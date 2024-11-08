import "./App.css";
import { publish } from "./helpers/client";
import { useState } from "react";
import data from "./helpers/data";

function App() {
  const [rooms, setRooms] = useState(data);
  const [selectedCheckbox, setSelectedCheckbox] = useState(null);

  const handleCheckboxChange = (index) => {
    setSelectedCheckbox(index);
  };

  return (
    <>
      <h1>SmartHome</h1>
      <h4>Me da gusto verte de nuevo</h4>

      <h3>Tus habitaciones</h3>
      {rooms.map((_, index) => (
        <div key={index}>
          <input
            type="checkbox"
            checked={selectedCheckbox === index}
            onChange={() => handleCheckboxChange(index)}
          />
          <label>{rooms[index].name}</label>
        </div>
      ))}

      <div>
        <h3>Dispositivos</h3>
        {selectedCheckbox !== null && (
          <>
            <h4>{rooms[selectedCheckbox].name}</h4>
            {Object.keys(rooms[selectedCheckbox]).map((key, index) => (
              <div key={index}>
                {key !== "name" && (
                  <div>
                    <label>{key}</label>
                    <input
                      type="checkbox"
                      checked={rooms[selectedCheckbox][key].on}
                      onChange={() => {
                        const newRooms = [...rooms];
                        newRooms[selectedCheckbox][key].on =
                          !newRooms[selectedCheckbox][key].on;
                        setRooms(newRooms);
                        publish(newRooms);
                      }}
                    />
                    {rooms[selectedCheckbox][key].value !== undefined && (
                      <input
                        type="range"
                        min="0"
                        max="100"
                        step="10"
                        value={rooms[selectedCheckbox][key].value}
                        onChange={(e) => {
                          const newRooms = [...rooms];
                          newRooms[selectedCheckbox][key].value = e.target.value;
                          setRooms(newRooms);
                          publish(newRooms);
                        }}
                      />
                    )}
                  </div>
                )}
              </div>
            ))}
          </>
        )}
      </div>
    </>
  );
}
export default App;
