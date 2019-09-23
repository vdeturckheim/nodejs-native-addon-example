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
RUN cd ${DIR}
RUN npm install
RUN npm t
