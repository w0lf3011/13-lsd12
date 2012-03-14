#!/bin/bash
if [ -z "$1" ]; then
echo "ERROR : parametre = login claretoile!!!"
exit 1
fi

if [ "$1" == "xpereman" ]; then

ssh -L 12345:concours.info.fundp.ac.be:80 xpereman@backus.info.fundp.ac.be

else

ssh -L 12345:concours.info.fundp.ac.be:80 $1@sunset.info.fundp.ac.be

fi

echo "Launch browser : http://localhost:12345/automate" 
