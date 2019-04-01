#!/usr/bin/env bash

tar -czvf $ARCHIVE_NAME_RELEASE *

git config --local user.name "frouioui"
git config --local user.email "florent.poinsard@epitech.eu"
export TRAVIS_TAG=${TRAVIS_TAG:-"pre"-$(date +'%d')/$(date +'%m')-$(date +'%H')h$(date +'%M')-$(git log --format=%h -1)}
git tag $TRAVIS_TAG