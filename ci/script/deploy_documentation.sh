#!/usr/bin/env bash

dnf install doxygen -y
make docs
rm -Rf include/ src/ tests/ ci/ Makefile lib/ .vscode/
mv docs/html/* .
rm -Rf docs/