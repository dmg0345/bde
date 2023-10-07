<#
.SYNOPSIS
    Management script based on PowerShell, this script must be executed from the root directory.
#>

# [Initializations] ####################################################################################################
param (
    # Command to execute, one of:
    #    'load': Host/Container command, loads the Powershell modules in the terminal for more granular access.
    #    'clean': Host/Container command, recursively cleans the repository and submodules with Git.
    #    'build': Host command, builds the images and the development containers.
    #    'run': Host command creates or uses an existing development container and starts it in the current folder.
    #    'clang-format': Container command, runs 'clang-format' project wide.
    #    'clang-tidy': Container command, runs 'clang-tidy' project wide.
    #    'cppcheck': Container command, runs 'cppcheck' and its MISRA addon project wide.
    #    'doc8': Container command, runs 'doc8' project wide.
    #    'test_report': Container command, runs 'junit2html' from a log file with 'CMocka' XML output project wide.
    #    'coverage': Container command, runs 'fastcov' and 'lcov' project wide.
    #    'docs': Container command, runs 'doxygen' and 'sphinx' project wide.
    [Parameter(Mandatory = $true)]
    [ValidateSet(
        "load", "clean", "build", "run", "clang-format", "clang-tidy", "cppcheck", "doc8", "test_report",
        "coverage", "docs"
    )]
    [String]
    $Command
)

# Stop on first error found.
$ErrorActionPreference = "Stop";

# Imports.
Import-Module "$PSScriptRoot/other/powershell/modules/commons.psm1";
Import-Module "$PSScriptRoot/other/powershell/modules/devcontainers.psm1";
Import-Module "$PSScriptRoot/other/powershell/modules/linters.psm1";
Import-Module "$PSScriptRoot/other/powershell/modules/tests.psm1";
Import-Module "$PSScriptRoot/other/powershell/modules/documentation.psm1";

# [Declarations] #######################################################################################################
# Location of the CppCheck MIRSA rules file.
$CPPCHECK_MISRA_RULES_FILE = "other/cppcheck/cppcheck_misra_rules.txt";
# Path to 'devcontainer.json' file.
$DEVCONTAINER_FILE = ".devcontainer/devcontainer.json"; 
# Project name for the Docker compose project.
$DEVCONTAINER_PROJECT_NAME = "bde_c_cpp";

# [Internal Functions] #################################################################################################

# [Functions] ##########################################################################################################

# [Execution] ##########################################################################################################
# Ensure the current location is the location of the script and it is the root of a Git repository.
if ((-not (Test-Path ".git")) -or (((Get-Item "$PSScriptRoot").Hashcode) -ne ((Get-Item "$PWD").Hashcode)))
{
    throw "The script must run from the root directory of the repository, where this script is located."
}

if ($Command -eq "load")
{
    # The modules have already been imported due to the imports above, perform no other action.
    Write-Log "Modules imported." "Success";
}
elseif ($Command -eq "clean")
{
    Write-Log "Cleaning repository and submodules...";
    git clean -d -fx -f;
    git submodule foreach --recursive git clean -d -fx -f;
    Write-Log "Repository and submodules cleaned." "Success";
}
elseif ($Command -eq "build")
{
    # Build inputs for the development container.
    $inputs = @{
        
    };

    # Build outputs for the development container.
    $outputs = @{
        # This is the 'poetry.lock' file generated by Python environment, with all the dependencies.
        "Python Poetry lock file" = @{
            "containerPath" = "/usr/venvs/poetry.lock";
            "hostPath"      = "poetry.lock";
        }
    };
    
    Initialize-DevContainer -DevcontainerFile "$DEVCONTAINER_FILE" -ProjectName "$DEVCONTAINER_PROJECT_NAME" `
        -Inputs $inputs -Outputs $outputs;
}
elseif ($Command -eq "run")
{
    # Artifacts to copy in the workspace each time the development container is run.
    $inputs = @{
        # This is the CppCheck MISRA Rules file, which is copied from the host to the workspace.
        # 
        # This file should not be commited to the repository, keep the '.gitignore' updated.
        "CppCheck MISRA Rules" = @{
            "srcPath"  = "../../Local/misra-files/misra-c-2012/cppcheck_misra_rules.txt";
            "destPath" = "$CPPCHECK_MISRA_RULES_FILE";
        };
    };

    Start-DevContainer -DevcontainerFile "$DEVCONTAINER_FILE" -ProjectName "$DEVCONTAINER_PROJECT_NAME" `
        -Inputs $inputs;
}
elseif ($Command -eq "clang-format")
{
    Start-ClangFormat -ClangFormatExe "clang-format-15" -Files ".cmake_build/psf.txt" -ConfigFile ".clang-format";
}
elseif ($Command -eq "clang-tidy")
{
    Start-ClangTidy -ClangTidyExe "clang-tidy-15" -Files ".cmake_build/psf.txt" -ConfigFile ".clang-tidy" `
        -CMakeBuildDir ".cmake_build";
}
elseif ($Command -eq "cppcheck")
{
    # Build regular expressions to check for analysis.
    $fileFilters = @(
        "src/*",
        "tests/tests/*"
    );

    Start-CppCheck `
        -CppCheckExe "cppcheck" -PythonExe "python" -CppCheckHTMLReportExe "cppcheck-htmlreport" -MaxJobs 1 `
        -CppCheckRulesFile "$CPPCHECK_MISRA_RULES_FILE" -SuppressionXML "other/cppcheck/suppressions.xml" `
        -CompileCommandsJSON ".cmake_build/compile_commands.json" -FileFilters $fileFilters `
        -CppCheckBuildDir "other/cppcheck/.build" -CppCheckReportDir "other/cppcheck/.report" -CppCheckSourceDir ".";
}
elseif ($Command -eq "doc8")
{
    # Folds and files where to run doc8.
    $inputs = @(
        "doc",
        "readme.rst"
    );

    Start-Doc8 -Doc8Exe "doc8" -ConfigFile "pyproject.toml" -Inputs $inputs;
}
elseif ($Command -eq "test_report")
{
    Start-CMockaHTML -JUnit2HTMLExe "junit2html" -OutputFolder "tests/.test_results";
}
elseif ($Command -eq "coverage")
{
    # Substrings of files that will be included in the report.
    $inputs = @(
        "src",
        "tests/tests"
    );

    Start-FastCov -FastCovExe "fastcov" -LCovGenHTMLExe "genhtml" -Include $inputs `
        -CoverageDir "tests/.coverage" -CMakeBuildDir ".cmake_build";
}
elseif ($Command -eq "docs")
{
    Start-DoxygenSphinx -DoxygenExe "doxygen" -SphinxBuildExe "sphinx-build" -ConfigFolder "doc" `
        -HTMLOutput "doc/.output/html";
}
else
{
    throw "Command '$Command' is not recognized or an invalid combination of arguments was provided.";
}
