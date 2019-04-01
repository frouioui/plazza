#!/usr/bin/env bash

cd $APPLICATION_DIRECTORY_DOCKER

ssh-keyscan git.epitech.eu >> ~/.ssh/known_hosts
git checkout $TRAVIS_BRANCH
git push --repo=git@git.epitech.eu:/florent.poinsard@epitech.eu/OOP_nanotekspice_2018 --force
