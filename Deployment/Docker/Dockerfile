# docker run --add-host raspberrypi:<ip of the server> <container_tag>
# or conveniently
# docker build . -t opcua && docker run -it --network=host --add-host raspberrypi:10.200.2.8 opcua
# Cagatay sudo  docker build . -t opcua && docker run -it --network=host --add-host raspberrypi:10.200.2.14 opcua
FROM ubuntu:xenial
RUN apt-get update && apt-get install -y gcc g++
ADD . /tests
#ADD ./hosts /etc/hosts
WORKDIR /tests
RUN gcc -std=c99 open62541.c filesize_test.c -o phase_3
CMD "./phase_3"
