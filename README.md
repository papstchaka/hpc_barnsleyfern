# hpc_barnsleyfarn

This repositoriy is directly related to <a href='https://www.ei.tum.de/ldv/startseite/' target='_blank'>`Lehrstuhl für Datenverarbeitung`</a> course <a href='https://www.ei.tum.de/ldv/lehre/high-performance-computing-fuer-maschinelle-intelligenz/' target='_blank'>`High Performance Computing for machine intelligence`</a> at TU Munich. Goal of the course was to use parallelism in combination with C++ to speed-up different kinds of algorithms. First, algorithms were implemented using multiple threads on one single machine, later on - using <a href='https://www.openmp.org/' target='_blank'>`OpenMP`</a> and <a href='https://www.open-mpi.org/' target='_blank'>`OpenMPI`</a> - on mulitple machines."

<br/><br/>

-------

## Goal

Parallel implementation of <a href="https://en.wikipedia.org/wiki/Barnsley_fern" target="_blank">`Barnsley Farn Algorithm`</a> in C++. Repository follows up the <a href="https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem" target="_blank">`producer-consumer-model`</a> and is aware of upcoming <a href="https://en.wikipedia.org/wiki/Race_condition" target="_blank">`race conditions`</a> (= threadsafe) by using mutexes. The implementation of the consumer-producer model is held modular, so it is very simple to change the desired algorithm without loosing a framework that works parallel and therefore very performant and efficient.

<br/><br/>

-------

## Usage

All requiered functionality to `compile`, `send` or `clean` the project is provided by given <a href="Makefile" target="_blank">`Makefile`</a>:
>   - `make compile` - deletes old executables, `tar`-archives and `build/` folder, builds a new executable (of new version) and moves this executable directly to root folder. That can afterwards be started by `./barnsley_fern`
>   - `make clean` - cleans project folder by removing old executables, `tar`-archives and `build/` folder
>   - `make send` - packs `src/` folder and `Makefile` into `tar` archive and sends it via `scp` to desired target
>   - `make unpack` - provides the possibility to untar the `tar` archive and rebuild the given folder structure at new place
>   - `./barnsley_fern` - starts the compiled script that produces the output image

More detailed information on algorithms' implementation and task of the respective scripts is given in <a href="src/" target="_blank">`src`</a>

<br/><br/>

-------

## Result

Algorithm produces a BarnsleyFern with high resolution (10k x 20k pixels), stored in a file named `barnsley_fern.png`. Standart working time for 2 consumers and 2 producers (with each 10^8 points) is `~6mins`. Desired resolution can be changed in <a href="src/RealConsumer.h" target="_blank">`RealConsumer.h`</a>

<br/><br/>

<h2 align="center">
  <img src="assets/barnsley_fern_result.PNG" alt="resulting barnsley fern" width="600px" />
</h2>

<br/><br/>

-------

## Requirements

### Recommended environment for compiling are <a href="https://docs.microsoft.com/en-us/windows/wsl/about" target="_blank">`Windows Subsystem for Linux`</a> or any other `linux-based` operating system!

> Install `cmake`, `gcc`, `clang`, `gdb` and `build-essential` by running
```cmd
sudo apt-get update
sudo apt-get install cmake gcc clang gdb built-essential
```

<br/><br/>

-------

## Supporting developers:
> -   <a href="https://github.com/papstchaka" target="_blank">`Alexander Christoph`</a> [implementation]
> -   <a href="https://www.ei.tum.de/ldv/team/wissenschaftliche-mitarbeiter/martin-gottwald/" target="_blank">`Martin Gottwald`</a> [concept / instructor]
> -   <a href="https://www.ei.tum.de/ldv/team/wissenschaftliche-mitarbeiter/alice-hein/" target="_blank">`Alice Hein`</a> [concept / instructor]