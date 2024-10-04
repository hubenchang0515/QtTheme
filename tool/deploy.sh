#! /usr/bin/bash
set -e
TARGET_REPO=$(git remote get-url origin)
TARGET_BRANCH="gh-pages"
TARGET_DIR=$1

if [ "$TARGET_DIR" == "" ]
then
    echo Pleas input target directory.
    exit 1
fi

cd $TARGET_DIR

if [ -e .git ]
then
    echo Target directory is invalid, '.git' exist.
    exit 1
fi

git init .
git remote add origin $TARGET_REPO
git checkout -b $TARGET_BRANCH
git add *
git commit -m "Update gh-pages"
git push origin $TARGET_BRANCH -f
rm -rf .git
