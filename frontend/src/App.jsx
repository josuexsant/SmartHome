import "./App.css";
import { publish } from "./helpers/client";
import data from "./helpers/data";

function App() {

  const handleClick = () => {
    publish(data);
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
