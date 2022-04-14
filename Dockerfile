FROM ubuntu:latest
WORKDIR /home/projects

RUN apt-get update&&apt-get install -y \
  make \
  vim \
  gcc \
  g++ \