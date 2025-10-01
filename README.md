# Functional Testing

## Prerequisites

- make
- g++

## Building instructions

The repo consists of 2 files, one for the boundary values analysis method and one for the decision table method. After building, the executables are located under `bin/`.

- Build all executables:
  ```
  make
  ```

- Build one executable:
  ```
  make bva
  ```
  or
  ```
  make dtt
  ```

- Run executable:
  ```
  make run bva
  ```
  or
  ```
  make run dtt
  ```

- Clean executables:
  ```
  make clean
  ```