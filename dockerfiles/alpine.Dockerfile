ARG NODE_VERSION
FROM node:$NODE_VERSION-alpine
ARG DIR
ARG AWS_ACCESS_KEY_ID=''

RUN apk add --update \
    python \
    python-dev \
    make \
    g++

WORKDIR /app/build
COPY . .
WORKDIR /app/build/${DIR}
RUN npm install
RUN node test
