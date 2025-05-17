import os
import shutil
import subprocess
import sys

# configuration
build_dir = "build"
cmake_args = [
    "..",
    "-DBUILD_SHARED_LIBS=OFF",
    "-DSDL_STATIC=ON",
    "-DSDL_SHARED=OFF"
]
build_config = "Release"

if not os.path.isdir(build_dir):
    os.makedirs(build_dir)

os.chdir(build_dir)

cache_file = "CMakeCache.txt"
if os.path.exists(cache_file):
    os.remove(cache_file)

try:
    subprocess.run(["cmake"] + cmake_args, check=True)
except subprocess.CalledProcessError as e:
    print("CMake configuration failed:", e)
    sys.exit(1)

try:
    subprocess.run(["cmake", "--build", ".", "--config", build_config], check=True)
except subprocess.CalledProcessError as e:
    print("Build failed:", e)
    sys.exit(1)

os.chdir("..")

print("Build completed successfully.")
