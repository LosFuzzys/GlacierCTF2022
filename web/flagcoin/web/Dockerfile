FROM node:19.0.0-bullseye
WORKDIR /app
COPY . .
EXPOSE 8080
RUN npm install .
CMD ["node", "/app/index.js"]
