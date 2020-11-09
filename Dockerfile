FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
  clang-9 \
  build-essential \
  g++ \
  cmake \
  clang-tidy-9

WORKDIR /usr/src
COPY . .

ENTRYPOINT ["scripts/entrypoint.sh"]

