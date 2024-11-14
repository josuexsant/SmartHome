import "./App.css";
import { publish } from "./helpers/client";
import { useEffect, useState } from "react";
import data from "./helpers/data";
import { useNavigate } from "react-router-dom";
import 'bootstrap/dist/css/bootstrap.min.css';
import 'bootstrap-icons/font/bootstrap-icons.css';

function App() {
  const navigate = useNavigate();
  const [rooms, setRooms] = useState(data);
  const [selectedCheckbox, setSelectedCheckbox] = useState(null);
  const [visit, setVisit] = useState(false);
  const { bedroomTemp, livingRoomTemp, bell } = useMessage();
  const [open, setOpen] = useState(true);

  useEffect(() => {
    setOpen(rooms[3].door.open);
  }, [rooms]);

  useEffect(() => {
    if (bedroomTemp !== null) {
      setRooms((prevRooms) => {
        const updatedRooms = [...prevRooms];
        updatedRooms[0].temperature = bedroomTemp;
        return updatedRooms;
      });
    }
  }, [bedroomTemp]);

  useEffect(() => {
    if (livingRoomTemp !== null) {
      setRooms((prevRooms) => {
        const updatedRooms = [...prevRooms];
        updatedRooms[3].temperature = livingRoomTemp;
        return updatedRooms;
      });
    }
  }, [livingRoomTemp]);

  useEffect(() => {
    if (bell !== null) {
      setRooms((prevRooms) => {
        const updatedRooms = [...prevRooms];
        updatedRooms[3].bell.value = bell;
        return updatedRooms;
      });

      if (bell < 5) {
        setVisit(true);
      } else {
        setVisit(false);
      }
    }
  }, [bell]);

  // TODO: Implementar el timbre de la puerta

  const handleCheckboxChange = (index) => {
    setSelectedCheckbox(index);
  };

  const handleButtonClick = () => {
    navigate("/unlock");
  };

  return (
    <>
  
    <div className="d-flex flex-column">
      <h1 className="fw-bolder" id="blue">SmartHome</h1>
      <span>Hola, Cesar</span>
      <span>Me da gusto verte de nuevo...</span>
    </div>

      

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
        <button
          onClick={() => {
            if (!open) {
              navigate("/unlock");
            } else {
              const newRooms = [...rooms];
              newRooms[3].door.open = !newRooms[3].door.open;
              setRooms(newRooms);
              setOpen(newRooms[3].door.open);
              publish(newRooms);
            }
          }}
        >
          {open ? "Cerrar" : "Abrir"}
        </button>
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
