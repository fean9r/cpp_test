#!/bin/bash


#########
# Usage #
#########

if [ $# -eq 0 ]
then
	echo "Usage: $0 <BranchName> [ <BranchName> [<BranchName> ...] ]"
	echo "Usage: $0 -r <StartRange> <EndRange> "
	echo "This will rebase those branches onto your current HEAD. We assume there is only one commit in every branch (QH workflow)"
	echo ""
	echo "  --- A -- B -- C    <--- HEAD"
	echo "           | "
	echo "           + -- K -- D -- E "
	echo ""
	echo "$> $0 D E"
	echo ""
	echo "  --- A -- B -- C -- D -- E    <--- HEAD"
	echo "           | "
	echo "           + -- K"
	echo ""
	echo ""

	echo "Example: $0 123654 321563 321456 ..."
	exit 0
fi

################
# Display tree #
################

if [ "$1" = "-t" ]
then
	git log --graph --oneline --all --decorate --color --simplify-by-decoration
	exit 0
fi



##################
# Branch rebases #
##################

BRANCH_LIST=$*

if [ "$1" = "-r" ]
then
	BRANCH_LIST=`git log --oneline --decorate --simplify-by-decoration ${2}~1..${3} | cut -f2 -d' ' | sed -e 's/^(//' -e 's/)$//' | tac`
fi

for branch in $BRANCH_LIST
do

	echo "________________________________"
	echo "                                "
	echo "    Rebase of branch $branch    "
	echo "________________________________"
	echo " ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨"
	git rebase -Xignore-space-change --onto HEAD $branch~1 $branch || exit 1

done

