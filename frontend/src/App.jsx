import "./App.css";
import { publish } from "./helpers/client";

function App() {

  const handleClick = () => {
    publish("Encenddido");
  };

  return (
    <>
      <h1>SmartHome</h1>
      <h4>Me da gusto verte de nuevo</h4>
      <hr />
      <br />
      <br />
      <br />
      <h2>Proximamente...</h2>
      <button onClick={handleClick}>Encender</button>
    </>
  );
}

export default App;
