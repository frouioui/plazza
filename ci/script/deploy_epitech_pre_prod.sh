#!/usr/bin/env bash

cd $APPLICATION_DIRECTORY_DOCKER

ssh-keyscan git.epitech.eu >> ~/.ssh/known_hosts
git checkout $TRAVIS_BRANCH
git push git@git.epitech.eu:/florent.poinsard@epitech.eu/CCP_plazza_2018 --force dev:dev