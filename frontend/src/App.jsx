import "./App.css";
import { publish } from "./helpers/client";
import { useEffect, useState } from "react";
import data from "./helpers/data";
import { useNavigate } from "react-router-dom";

function App() {
  const navigate = useNavigate();
  const [rooms, setRooms] = useState(data);
  const [selectedCheckbox, setSelectedCheckbox] = useState(null);
  const [visit, setVisit] = useState(false);

  // TODO: Implementar el timbre de la puerta
  useEffect(() => {
    setVisit([rooms[3].bell.on]);
  }, [rooms]);

  const handleCheckboxChange = (index) => {
    setSelectedCheckbox(index);
  };

  const handleButtonClick = () => {
    navigate("/unlock");
  };

  return (
    <>
      <h1>SmartHome</h1>
      <h2>¡Hola Cesar!</h2>
      <h4>Me da gusto verte de nuevo</h4>

      <div>
        {visit ? (
          <div>
            <h3>¡Ring Dong!</h3>
            <p>Tienes una visita</p>
            <p>A {[rooms[3].bell.value]} mts</p>
          </div>
        ) : (
          <h3>No tienes visitas</h3>
        )}
      </div>

      <div>
        <button onClick={handleButtonClick}>Abrir</button>
      </div>

      <h3>Tus habitaciones</h3>
      {rooms.map((_, index) => (
        <div key={index}>
          <label>{rooms[index].name}</label>
          <input
            type="checkbox"
            checked={selectedCheckbox === index}
            onChange={() => handleCheckboxChange(index)}
          />
          <p>
            {rooms[index].temperature ? `${rooms[index].temperature}ºC` : ""}
          </p>
        </div>
      ))}

      <div>
        {selectedCheckbox !== null && (
          <>
            <h3>Dispositivos</h3>
            <h4>{rooms[selectedCheckbox].name}</h4>
            {Object.keys(rooms[selectedCheckbox]).map((key, index) => (
              <div key={index}>
                {key !== "name" &&
                  key !== "temperature" &&
                  key !== "door" &&
                  key !== "bell" && (
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
                          max="255"
                          step="51"
                          value={rooms[selectedCheckbox][key].value}
                          onChange={(e) => {
                            const newRooms = [...rooms];
                            newRooms[selectedCheckbox][key].value =
                              e.target.value;
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
