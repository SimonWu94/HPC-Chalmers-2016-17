# Installing PLASMA

We download the PLASMA INSTALLER from the [PLASMA website](http://www.netlib.org/plasma/) onto Ozzy with `wget`. i.e:

```sh
wget http://icl.cs.utk.edu/projectsfiles/plasma/pubs/plasma-installer.tar.gz
```
We unpack the zip file into the `~/plasma_local` using the command:

```sh
tar xf plasma-installer.tar.gz -C ~/plasma_local
```

When installing PLASMA, we have the choice to give a path to the BLAS and LAPACK libraries already present on Ozzy. If we take a look at `/usr/local`, we find those two libraries there. Looking closely, we see both `.a` and `.so` file extensions for the libraries, which correspond to the static and dynamic library respectively. The main differences are that when we incorporate static libraries into our processes, the used library functions are directly embedded into our process code during compile time. In comparison, dynamic libraries are only called upon during run time from our processes. As a result, processes with static libraries are usually bigger in size than their counterparts that reference dynamic libraries. However, speed from referencing dynamic libraries might dwindle when there are a lot of function calls to those libraries. Individual tests have to be made for particular processes in order to determine whether or not this difference is significant. 

In our installation, we chose to link the static libraries on the fact that we have copious amounts of memory. (However, the programs we are dealing with during this course will probably not show any significant difference anyhow.)


Hence, we call the instruction:

```sh
./setup.py --prefix="../../plasma_local" \
           --blaslib="/usr/lib/libblas/libblas.a" \
           --lapacklib="/usr/lib/liblapack.a" \
           --notesting 
```

Which installs PLASMA under the path `~/plasma_local` as required by the assignment. And we finish the first part


# Testing PLASMA
To test PLASMA, we change directory to `~/plasma-installer_2.8.0/build/plasma_2.8.0/testing`, there we find all the test files. To run all the tests (the simple tests) at once we run the instruction:
```sh
.\plasma_testing.py 
```
The default number of cores used is half of the total present on Ozzy. In this case we used 28 cores. After a coffee and finishing the Encyclopedia, we finished testing. A quick look into the `testing_results.txt` and searching for ailed tests, we do not find any (very suspicious...). We conclude the installation was a success.

# Makefile inspection 

For the assignment, we go to the `testing` directory. There we find our first makefile. Opening it we find that it includes other makefiles...

Let's go on makefile hunting!!

The included external makefiles we find are:

 * `include ../Makefile.internal` which defines the paths of the PLASMA libraries, and groups all the libraries into a variable called LIB to be used later. `include ../Makefile.internal` actually depends further on three other Makefiles:

     *  `include $(PLASMA_DIR)/make.inc` which sets all the variables for the compiler, such as: CC=cc,FC= gfortran ... as well as providing the paths to the BLAS, CBLAS LAPACK and CLAPACK libraries.)

     * `-include $(PLASMA_DIR)/make.inc.${MACHINE}` (This one does not exist...the variable MACHINE is not even defined, probably due to the INSTALLER not making it)

     * `-include $(PLASMA_DIR)/Makefile.gen` (which also does not exist...)


 * `-include Makefile.src` to group all the test files in source code written in c into variables. We obtain three variables: CSRC , DSRC and SSRC.

At last, having found all the dependecies between the makefiles, the main makefile called Makefile is called and builds our executables. 
