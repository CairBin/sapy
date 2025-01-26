#!/bin/sh

conan create . --build=missing -s build_type=Debug
conan create . --build=missing -s build_type=Release
