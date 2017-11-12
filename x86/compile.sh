#!/bin/bash

OUT_DIR=`pwd`"/out"
OBJ_DIR="${OUT_DIR}/obj"
BIN_DIR="${OUT_DIR}/bin"

CLIENT_OBJ_DIR="${OBJ_DIR}/client"
CLIENT_SRC_DIR=`pwd`"/client"
TARGET_CLIENT="${BIN_DIR}/client_app"

SERVER_OBJ_DIR="${OBJ_DIR}/server"
SERVER_SRC_DIR=`pwd`"/server"
TARGET_SERVER="${BIN_DIR}/server_app"

#CC=echo
CC=gcc
CC_OPTIONS="-Wall"

function print_usage {
  echo "compile.sh <target>"
  echo "compiles files in this folder"
  echo "Targets:"
  echo " client  <-- makes client app"
}

function make_client {
  mkdir -p "${CLIENT_OBJ_DIR}"
  rm -rf "${CLIENT_OBJ_DIR}/*"
  rm -f ${TARGET_CLIENT}

  ${CC} ${CC_OPTIONS} ${CLIENT_SRC_DIR}/client.c -c -o ${CLIENT_OBJ_DIR}/client.o
  ${CC} ${CC_OPTIONS} ${CLIENT_SRC_DIR}/actions.c -c -o ${CLIENT_OBJ_DIR}/actions.o
  ${CC} ${CC_OPTIONS} ${CLIENT_SRC_DIR}/main.c -c -o ${CLIENT_OBJ_DIR}/main.o

  ${CC} ${CLIENT_OBJ_DIR}/client.o ${CLIENT_OBJ_DIR}/actions.o ${CLIENT_OBJ_DIR}/main.o -o ${TARGET_CLIENT}
}

function make_server {
  mkdir -p "${SERVER_OBJ_DIR}"
  rm -rf "${SERVER_OBJ_DIR}/*"
  rm -f ${TARGET_SERVER}

  ${CC} ${CC_OPTIONS} ${SERVER_SRC_DIR}/server.c -c -o ${SERVER_OBJ_DIR}/server.o
#  ${CC} ${CC_OPTIONS} ${SERVER_SRC_DIR}/actions.c -c -o ${CLIENT_OBJ_DIR}/actions.o
  ${CC} ${CC_OPTIONS} ${SERVER_SRC_DIR}/main.c -c -o ${SERVER_OBJ_DIR}/main.o

  ${CC} ${SERVER_OBJ_DIR}/server.o ${SERVER_OBJ_DIR}/main.o -o ${TARGET_SERVER}
}

# =============================================================================

case "$1" in

  "client")  echo "Making client app"
    make_client
    ;;
  "server")  echo  "Making server app"  
    make_server
    ;;
  -h)  print_usage
    ;;
  --help) print_usage
   ;;
  *) echo "ERROR: incorrect usage"
   ;;
esac




