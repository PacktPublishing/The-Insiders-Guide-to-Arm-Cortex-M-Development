FROM ubuntu:22.04 as base

ENV USER=ubuntu 

ARG CMSIS_5

RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

RUN apt-get update 
RUN apt-get install -y --no-install-recommends apt-utils
RUN apt-get -y upgrade
RUN apt-get -y --no-install-recommends install sudo vim ca-certificates wget curl jq git unzip bzip2 make cmake gdb-multiarch automake autoconf libtool libftdi-dev libusb-1.0-0-dev pkg-config clang-format

RUN useradd --create-home -s /bin/bash -m $USER && echo "$USER:$USER" | chpasswd && adduser $USER sudo
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

WORKDIR /home/$USER
USER ubuntu

RUN wget https://github.com/ARM-software/CMSIS_5/archive/refs/tags/${CMSIS_5}.zip  && unzip ${CMSIS_5}.zip && rm ${CMSIS_5}.zip && ln -s  CMSIS_5-${CMSIS_5} CMSIS_5
RUN wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh
RUN chmod +x /home/$USER/pico_setup.sh
RUN SKIP_VSCODE=1 SKIP_UART=1 /home/$USER/pico_setup.sh

FROM base as vscode

ARG VSCODE
ARG VSCODE_SERVER_PATH 
ARG VSCODE_DL_PATH 
ENV VSCODE_HOME=$VSCODE_SERVER_PATH

# Install VSCODE
RUN wget https://github.com/gitpod-io/openvscode-server/releases/download/${VSCODE_DL_PATH}/${VSCODE}
RUN tar xf /home/$USER/$VSCODE -C /home/$USER
RUN rm /home/$USER/$VSCODE

RUN git clone https://github.com/jasonrandrews/dotprod-pico.git

EXPOSE 3000

ENTRYPOINT  [ "/bin/sh", "-c", "exec ${VSCODE_HOME}/bin/openvscode-server --host 0.0.0.0 --port 3000 --without-connection-token \"${@}\"", "--" ]
