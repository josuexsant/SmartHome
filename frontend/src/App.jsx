import "./App.css";
import { publish } from "./helpers/client";
import { useState } from "react";
import data from "./helpers/data";

function App() {
  const [selectedCheckbox, setSelectedCheckbox] = useState(null);

  const handleClick = () => {
    publish(data);
  };

  const handleCheckboxChange = (index) => {
    setSelectedCheckbox(index);
  };

  return (
    <>
      <h1>SmartHome</h1>
      <h4>Me da gusto verte de nuevo</h4>
      <hr />
      <br />
      <br />
      <br />

      {["Dormitorio,"].map((_, index) => (
        <div key={index}>
          <input
            type="checkbox"
            checked={selectedCheckbox === index}
            onChange={() => handleCheckboxChange(index)}
          />
          Checkbox {index + 1}
        </div>
      ))}

      <button onClick={handleClick}>Encender</button>
    </>
  );
}

export default App;
