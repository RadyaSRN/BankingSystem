FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential cmake libgtest-dev

WORKDIR /

RUN mkdir bank_system_project

WORKDIR /bank_system_project

COPY . .

RUN mkdir build && cd build && cmake .. && make

WORKDIR /bank_system_project/bin
