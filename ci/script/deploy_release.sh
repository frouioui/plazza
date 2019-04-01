#!/usr/bin/env bash

tar -czvf $ARCHIVE_NAME_RELEASE *

git config --local user.name "YOUR GIT USER NAME"
git config --local user.email "YOUR GIT USER EMAIL"
export TRAVIS_TAG=${TRAVIS_TAG:-"official"-$(date +'%d')/$(date +'%m')-$(date +'%H')h$(date +'%M')-$(git log --format=%h -1)}
git tag $TRAVIS_TAG