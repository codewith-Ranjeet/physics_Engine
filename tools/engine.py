import argparse
import os
import platform
import shutil
import subprocess
import sys
from pathlib import Path


# --------------------------------------------------
# Project paths
# --------------------------------------------------

ROOT_DIR = Path(__file__).resolve().parent.parent

BUILD_DIR = ROOT_DIR / "build"
BIN_DIR = ROOT_DIR / "bin"
DEPS_DIR = ROOT_DIR / ".deps"
SFML_SOURCE_DIR = DEPS_DIR / "sfml-src"
SFML_BUILD_DIR = DEPS_DIR / "sfml-build"


# --------------------------------------------------
# Helpers
# --------------------------------------------------

def run(command):
    """Run a command and stop if it fails."""
    print(f"\n> {' '.join(command)}\n")

    result = subprocess.run(command, cwd=ROOT_DIR)

    if result.returncode != 0:
        sys.exit(result.returncode)


def find_cmake():
    """Make sure CMake is installed."""
    cmake = shutil.which("cmake")

    if cmake is None:
        print("Error: CMake was not found in PATH.")
        sys.exit(1)

    return cmake


def executable_name():
    """Return the correct executable name for the OS."""
    if platform.system() == "Windows":
        return "engine.exe"

    return "engine"


def dependencies_exist():
    """Check whether SFML dependencies have already been prepared."""
    sfml_cmake = SFML_SOURCE_DIR / "CMakeLists.txt"

    return sfml_cmake.exists()


# --------------------------------------------------
# Commands
# --------------------------------------------------

def deps():
    """
    Prepare/download project dependencies.

    This command is responsible for making sure SFML
    exists inside .deps/.
    """

    if dependencies_exist():
        print("SFML source already exists.")
        print("Dependencies are already prepared.")
        return

    print("SFML source not found.")
    print("Preparing dependencies...")

    cmake = find_cmake()

    run([
        cmake,
        "-S", str(ROOT_DIR),
        "-B", str(BUILD_DIR),
        "-DENGINE_FETCH_DEPS=ON"
    ])

    print("\nDependencies prepared successfully!")


def build():
    """
    Build the engine.

    This command NEVER downloads dependencies.
    Dependencies must already exist.
    """

    if not dependencies_exist():
        print("Error: Dependencies have not been prepared.")
        print("Run 'engine deps' first.")
        sys.exit(1)

    cmake = find_cmake()

    run([
        cmake,
        "-S", str(ROOT_DIR),
        "-B", str(BUILD_DIR),
        "-DENGINE_FETCH_DEPS=OFF"
    ])

    run([
        cmake,
        "--build", str(BUILD_DIR),
        "--config", "Release"
    ])

    print("\nBuild successful!")


def start():
    """Run the compiled engine."""

    executable = BIN_DIR / executable_name()

    if not executable.exists():
        print("Error: engine executable not found.")
        print("Run 'engine build' first.")
        sys.exit(1)

    run([str(executable)])


def remove_readonly(func, path, exc_info):
    """
    Make a read-only file writable and retry the operation.
    Needed mainly for Windows when deleting fetched dependencies.
    """
    os.chmod(path, 0o700)
    func(path)


def clean():
    """Remove build files but keep dependencies."""
    if BIN_DIR.exists():
        shutil.rmtree(BIN_DIR, onerror=remove_readonly)

    if BUILD_DIR.exists():
        shutil.rmtree(BUILD_DIR, onerror=remove_readonly)
        print("Build directory removed.")
    else:
        print("Nothing to clean.")


def deep_clean():
    """Remove build files and downloaded dependencies."""

    clean()

    if DEPS_DIR.exists():
        shutil.rmtree(DEPS_DIR, onerror=remove_readonly)
        print("Dependency directory removed.")
    else:
        print("No dependency directory found.")

    print("Deep clean complete.")


def rebuild():
    """Clean and build without downloading dependencies."""

    clean()
    build()


# --------------------------------------------------
# CLI
# --------------------------------------------------

def main():

    parser = argparse.ArgumentParser(
        prog="engine",
        description="Physics Engine development tool"
    )

    subparsers = parser.add_subparsers(dest="command")

    subparsers.add_parser(
        "deps",
        help="Prepare/download project dependencies"
    )

    subparsers.add_parser(
        "build",
        help="Build the engine"
    )

    subparsers.add_parser(
        "start",
        help="Run the engine"
    )

    subparsers.add_parser(
        "clean",
        help="Remove build files"
    )

    subparsers.add_parser(
        "rebuild",
        help="Clean and build the engine"
    )

    subparsers.add_parser(
        "deep-clean",
        help="Remove build files and downloaded dependencies"
    )

    args = parser.parse_args()

    if args.command == "deps":
        deps()

    elif args.command == "build":
        build()

    elif args.command == "start":
        start()

    elif args.command == "clean":
        clean()

    elif args.command == "rebuild":
        rebuild()

    elif args.command == "deep-clean":
        deep_clean()

    else:
        parser.print_help()


if __name__ == "__main__":
    main()