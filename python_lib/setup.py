from setuptools import setup

# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import sys

__version__ = "0.0.1"

# The main interface is through Pybind11Extension.

ext_modules = [
    Pybind11Extension("TicTacToe",
        ["src/TicTacToe.cpp"],
        # Example: passing in the version to the compiled code
        define_macros = [('VERSION_INFO', __version__)],
        ),
]

setup(
    name="TicTacToe",
    version=__version__,
    url="https://github.com/pybind/python_example",  # Example taken from this repository
    description="A test project using pybind11",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
