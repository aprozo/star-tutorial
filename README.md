# STAR Environment Tutorial [![Github Codespace](https://img.shields.io/badge/open-GH_Codespaces-blue?logo=github)](https://codespaces.new/aprozo/star-tutorial?quickstart=1)



For successfull running on Github Codespaces one can submit an application for Free [Github Education](https://github.com/education) benefits.

This is an example analysis of [`StPicoDst`](https://www.star.bnl.gov/webdata/dox/html/classStPicoDstMaker.html):
- `St` stands for STAR, [all classes](https://www.star.bnl.gov/webdata/dox/html/annotated.html) start from it 
- `Pico` means the tree data format where only small number of numerous qualities are saved, exist also `Micro` and `Mini`,
- `Dst` means Data Summary Table)


It is based on [Grigory's presentation on PicoDst 2019](https://drupal.star.bnl.gov/STAR/system/files/Nigmatkulov_intro2pico_Krakow2019.pdf)


## Learning Goals
1. Understand what `StRoot` is and why STAR code is placed there.
2. Understand what  [`cons` command](https://www.gnu.org/software/cons/stable/cons.html) does and what `.sl7X_gccXX` means.
3. Build and run one STAR maker.
4. Produce one user tree (`MyTreeEvent` + `MyTrack`) and read it.

## Essential Project Layout
```text
StRoot/StPicoDstAnalysisMaker/      # user STAR package compiled by cons
MyTreeEvent.h / MyTrack.h           # custom classes stored in output TTree
macros/runPicoDstAnalysisMaker.C    # run maker
macros/readMyTreeEvent.C            # read TTree with custom classes (no STAR)

```
## Core Concepts
### What is `StRoot`?
`StRoot` is the STAR source tree location where analysis packages are expected.

### Why do we need `StRoot` in this project?
`cons` discovers and builds STAR packages from `StRoot/<PackageName>`.  
If code is outside this structure, your package library is usually not built in the standard STAR way.

### What is `cons`?
`cons` is STAR's build command (similar role to `make`): it compiles C++ code and creates shared libraries used by ROOT macros.

### What happens during `cons`?
1. STAR platform/compiler setup is read.
2. Build directory `.sl7X_gccXX` is created or updated.
3. Code under `StRoot/` is compiled.
4. Shared libraries are written to `.sl7X_gccXX/LIB`.

### What is `.sl7X_gccXX`?
A STAR build-output directory name:
- `sl7X`: Scientific Linux 7 compatible build target.
- `gccXX`: compiler tag.

Example: `.sl79_gcc485` means SL7.9 target with GCC 4.8.5 toolchain.

### What is `gcc485` (`gcc4.8.5`)?
`gcc485` is shorthand for GNU C++ compiler version `4.8.5`.  
STAR uses fixed toolchains for binary compatibility across libraries.

## Minimal Workflow
Run from project root:

```bash
star-shell
cons
ls -d .sl*_gcc*/LIB
root -l -b -q 'macros/runPicoDstAnalysisMaker.C("/workspaces/star-tutorial/st_physics_20069002_raw_1500008.picoDst.root","outputPicoAnaMaker.root",-1)'
root -l -b -q 'macros/makeQaPdf.C("outputPicoAnaMaker.root","qa_report.pdf")'
```

## Remark: Running on your own laptop
In case you want to enter and run STAR container on your own laptop:

- You need to install either [Docker engine](https://docs.docker.com/get-started/get-docker/) or [Apptainer (singularity)](https://apptainer.org/docs/admin/main/installation.html).
For simplier Apptainer (singularity) installation:
```bash
sudo apt update
sudo apt install -y software-properties-common
sudo add-apt-repository -y ppa:apptainer/ppa
sudo apt update
sudo apt install -y apptainer
```
 - And then run commands:
```bash
git clone https://github.com/aprozo/star-tutorial.git
cd star-tutorial
apptainer run docker://ghcr.io/star-bnl/star-sw:main-root5-gcc485 bash -l
```
### Important! 
Do not forget to comment in your `~/.bashrc` sourcing your local Root installation (`source /path/thisroot.sh`), otherwise there will be a conflict of 2 ROOT versions: one - from your local installation, another - from STAR container.

- You may also create a shortcut for `star-shell` using code below:
```bash
mkdir -p ~/.local/bin && cat >~/.local/bin/star-shell <<'EOF'
#!/usr/bin/env bash
apptainer run  docker://ghcr.io/star-bnl/star-sw:main-root5-gcc485 "$@"
EOF
chmod +x ~/.local/bin/star-shell
grep -qxF 'export PATH="$HOME/.local/bin:$PATH"' ~/.bashrc || echo 'export PATH="$HOME/.local/bin:$PATH"' >>~/.bashrc
export PATH="$HOME/.local/bin:$PATH"
```


## Some old presentation on DST tutorials:

- [Introduction to PicoDst](https://drupal.star.bnl.gov/STAR/system/files/Nigmatkulov_intro2pico_Krakow2019.pdf) (Grigory Nigmatkulov, 2019)
- [Starting Data Analysis on STAR](http://nuclear.ucdavis.edu/~brovko/GettingStarted.pdf) (Samantha Brovko, 2011)
- [A common-MuDst tutorial](https://www.star.bnl.gov/public/comp/meet/RM200311/MuDstTutorial.pdf) (Sergey Panitkin, 2003)



