FROM quay.io/pypa/manylinux2010_x86_64
ARG NODE_VERSION
ARG DIR

WORKDIR /app/build
COPY . .

WORKDIR /
RUN curl "https://nodejs.org/dist/v${NODE_VERSION}/node-v${NODE_VERSION}-linux-x64.tar.gz" > "node-v${NODE_VERSION}-linux-x64.tar.gz"
RUN tar -xvf "node-v${NODE_VERSION}-linux-x64.tar.gz"
RUN ln -s "/node-v${NODE_VERSION}-linux-x64/bin/node" /bin/node
RUN ln -s "/node-v${NODE_VERSION}-linux-x64/bin/npm" /bin/npm

WORKDIR /app/build/
RUN cd ${DIR}
RUN npm install
RUN npm t
