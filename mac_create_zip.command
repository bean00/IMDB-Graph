#!/bin/bash
ZIP=HW7Submit

mydir="$(dirname "$BASH_SOURCE")"
cd $mydir

mkdir $ZIP
mkdir $ZIP/Mac.xcodeproj
mkdir $ZIP/StanfordCPPLib

cp * $ZIP
cp -R StanfordCPPLib/* $ZIP/StanfordCPPLib
cp -R Mac.xcodeproj/* $ZIP/Mac.xcodeproj

zip -r $ZIP.zip $ZIP

rm -rf $ZIP
