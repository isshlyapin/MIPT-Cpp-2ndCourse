#!/usr/bin/bash

ln -s $(getent passwd $USER | cut -d: -f6) $HOME
