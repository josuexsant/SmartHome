import mqtt from "mqtt";
import { useState, useEffect } from "react";

const useClient = () => {
  const [json, setJson] = useState(null);

  useEffect(() => {
    const client = mqtt.connect("wss://broker.emqx.io:8084/mqtt");
    const topic = "cesar";

    client.on("connect", () => {
      console.log("Conexión exitosa");
      client.subscribe(topic);
      console.log("Subscrito al tópico: " + topic);
    });

    client.on("error", (e) => {
      console.log("Fallo en la conexión: " + e.errorMessage);
    });

    client.on("message", (topic, message) => {
      const parsedMessage = JSON.parse(message.toString());
      console.log(parsedMessage);
      setJson(parsedMessage);
    });

    return () => {
      client.end();
    };
  }, []);

  return { json };
};

const publish = (message) => {
  const client = mqtt.connect("wss://broker.emqx.io:8084/mqtt");
  const topic = "cesar";
  const jsonMessage = JSON.stringify(message);
  client.publish(topic, jsonMessage);
};

export { useClient, publish };