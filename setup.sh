export ArNeuT_WD=`pwd`
export ArNeuT_LIB_PATH=$ArNeuT_WD/lib/
mkdir -p $ArNeuT_LIB_PATH
mkdir -p $ArNeuT_WD/tar

export ArNeuTV="Run1_v1"
mkdir -p $ArNeuT_WD/data/$ArNeuTV
export DATA_DIR=$ArNeuT_WD/data/$ArNeuTV

#### USER INFO ####
export ArNeuTLogEmail='sungbin.oh@cern.ch'
export ArNeuTLogWeb=''
export ArNeuTLogWebDir=''

#### use cvmfs for root ####
echo "@@@@ Setup output directories"
export ArNeuTRunlogDir=$ArNeuT_WD/output/log
export ArNeuTOutputDir=$ArNeuT_WD/output/result

alias pdout="cd $ArNeuTOutputDir"

export MYBIN=$ArNeuT_WD/bin/
export PYTHONDIR=$ArNeuT_WD/python/
export PATH=${MYBIN}:${PYTHONDIR}:${PATH}

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$ArNeuT_WD/AnalyzerTools/include/:$ArNeuT_WD/Analyzers/include/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ArNeuT_LIB_PATH

source $ArNeuT_WD/bin/BashColorSets.sh

## submodules ##
#source bin/CheckSubmodules.sh

## Todo list ##
python python/PrintToDoLists.py
source $ArNeuT_WD/tmp/ToDoLists.sh
rm $ArNeuT_WD/tmp/ToDoLists.sh

## Log Dir ##
echo "* Your Log Directory Usage"
#du -sh $ArNeuTRunlogDir
echo "-----------------------------------------------------------------"
CurrentGitBranch=`git branch | grep \* | cut -d ' ' -f2`
printf "> Current ArNeuT_NueCC branch : "${BRed}$CurrentGitBranch${Color_Off}"\n"
