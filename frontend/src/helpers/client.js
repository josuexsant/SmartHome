import mqtt from "mqtt";
import useMessage from "../hooks/useMessage";

// var client = new Paho.MQTT.Client("broker.emqx.io", 8084, clientId);
const client = mqtt.connect("wss://broker.emqx.io:8084/mqtt");
const topic = "cesar";

/**
 *  function onConnect() {
      console.log("Conexion exitosa...");
      client.subscribe("torneo");
      console.log("Suscrito al tópico 'torneo'");
    }             
 */
client.on("connect", () => {
  console.log("Conexión exitosa");
  client.subscribe(topic);
  console.log("Subscrito al tópico: " + topic);
});

/**
 *  function doFail(e) {
      console.log("Fallo en la conexión: " + e.errorMessage);
    }
 */
client.on("error", (e) => {
  console.log("Fallo en la conexión: " + e.errorMessage);
});

/**
 *  function onMessageArrived(message) {
      console.log("Un mensaje ha llegado: " + message.payloadString);
      var messagesDiv = document.getElementById("messages");
      messagesDiv.innerHTML = "";
      var newMessage = document.createElement("p");
      newMessage.textContent = message.payloadString;
      messagesDiv.appendChild(newMessage);
    }
 */

client.on("message", (topic, message) => {
  console.log("Un mensaje ha llegado: " + message.toString());
  const { setMessage } = useMessage();
  const parsedMessage = JSON.parse(message.toString());
  setMessage(parsedMessage);
});

/**
 *  function command(value) {
      console.log(value);
      var message = new Paho.MQTT.Message(value.toString());
      message.destinationName = "torneo";
      client.send(message);
    }
 */
export const publish = (message) => {
  const jsonMessage = JSON.stringify(message);
  client.publish(topic, jsonMessage);
};

export default publish;
