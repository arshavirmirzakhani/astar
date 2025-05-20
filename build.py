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
build_config = "Debug"

if not os.path.isdir(build_dir):
    os.makedirs(build_dir)

os.chdir(build_dir)

try:
    subprocess.run(["cmake"] + cmake_args)
except subprocess.CalledProcessError as e:
    print("CMake configuration failed:", e)
    sys.exit(1)

try:
    subprocess.run(["cmake", "--build", ".", "--config", build_config])
except subprocess.CalledProcessError as e:
    print("Build failed:", e)
    sys.exit(1)

os.chdir("..")

print("Build completed successfully.")
