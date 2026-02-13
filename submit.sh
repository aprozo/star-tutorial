#!/bin/bash 
cd submit
mkdir -p scheduler/ log/ production/
star-submit-beta batch.xml
