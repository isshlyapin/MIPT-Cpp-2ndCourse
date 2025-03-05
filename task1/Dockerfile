FROM ubuntu:24.04

WORKDIR /tools

RUN apt update

RUN apt install -y git-all wget gcc g++ cmake lsb-release software-properties-common gnupg

RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 19 all

RUN wget https://github.com/conan-io/conan/releases/download/2.13.0/conan-2.13.0-amd64.deb
RUN apt install -y ./conan-2.13.0-amd64.deb

RUN conan config install https://github.com/isshlyapin/conan_config.git

WORKDIR /app
