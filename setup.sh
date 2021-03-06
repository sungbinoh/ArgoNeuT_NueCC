export ArNeuT_WD=`pwd`
export ArNeuT_LIB_PATH=$ArNeuT_WD/lib/
mkdir -p $ArNeuT_LIB_PATH
mkdir -p $ArNeuT_WD/tar

export ArNeuTV="v1"
mkdir -p $ArNeuT_WD/data/$ArNeuTV
export DATA_DIR=$ArNeuT_WD/data/$ArNeuTV

#### USER INFO ####
export ArNeuTLogEmail='sungbin.oh@cern.ch'
export ArNeuTLogWeb=''
export ArNeuTLogWebDir=''

#### Setup Directories ####
#source /usr/local/bin/thisroot.sh
export CMS_PATH=/cvmfs/cms.cern.ch
source $CMS_PATH/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc700
export cmsswrel='cmssw-patch/CMSSW_10_4_0_patch1'
cd /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/src
echo "@@@@ SCRAM_ARCH = "$SCRAM_ARCH
echo "@@@@ cmsswrel = "$cmsswrel
echo "@@@@ scram..."
eval `scramv1 runtime -sh`
cd -
source /cvmfs/cms.cern.ch/$SCRAM_ARCH/cms/$cmsswrel/external/$SCRAM_ARCH/bin/thisroot.sh

echo "@@@@ Setup output directories"
export ArNeuTRunlogDir=$ArNeuT_WD/output/log
export ArNeuTOutputDir=$ArNeuT_WD/output/result

alias pdout="cd $ArNeuTOutputDir"

export MYBIN=$ArNeuT_WD/bin/
export PYTHONDIR=$ArNeuT_WD/python/
export PATH=${MYBIN}:${PYTHONDIR}:${PATH}

export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$ArNeuT_WD/DataFormats/include/:$ArNeuT_WD/AnalyzerTools/include/:$ArNeuT_WD/Analyzers/include/
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
