import "./App.css";
import { publish } from "./helpers/client";
import { useEffect, useState } from "react";
import data from "./helpers/data";
import { useNavigate } from "react-router-dom";
import "bootstrap/dist/css/bootstrap.min.css";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
  faLock,
  faBell,
  faCircleUser,
  faBed,
  faBath,
  faCouch,
  faFireBurner,
  faQuestionCircle,
  faLightbulb,
  faFan,
  faWind,
  faFaucet,
  faTv,
  faBurn,
  faUnlockAlt,
} from "@fortawesome/free-solid-svg-icons";
import useMessage from "./hooks/useMessage.js";

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

  const iconMap = {
    bedroom: faBed,
    bathroom: faBath,
    livingRoom: faCouch,
    kitchen: faFireBurner,
  };

  const RoomList = ({ rooms, navigate }) => {
    const [selectedButton, setSelectedButton] = useState(null);
  };

  const handleButtonClick = () => {
    navigate("/unlock");
  };

  const [selectedButton, setSelectedButton] = useState(null);

  const changeHabitation = (index) => {
    setSelectedButton(index);
    setSelectedCheckbox(index);
  };

  const icons = {
    light: faLightbulb,
    ceilingFan: faFan,
    air: faWind,
    waterService: faFaucet,
    tv: faTv,
    gasService: faBurn,
  };

  return (
    <>
      <div className="container-fluid py-5 px-4">
        <div className="row">
          <div className="col-10">
            <div className="d-flex flex-column justify-content-start  lh-sm">
              <h1 className="fw-bolder fs-2 blue m-0" id="blue">
                SmartHome
              </h1>
              <span className="fs-4">Hola, Cesar</span>
              <span className="text-truncate fs-6">
                Me da gusto verte de nuevo...
              </span>
            </div>
          </div>
          <div className="col-2 d-flex justify-content-end align-items-center">
            <FontAwesomeIcon
              className="blue person-circle ms-3"
              icon={faCircleUser}
            />
          </div>
        </div>

        <div className="row g-3 mt-3">
          <div className="col-8">
            <div className="container-funtions d-flex align-items-center gap-3 w-100 shadow-sm">
              <FontAwesomeIcon className="blue fs-3 ms-3" icon={faBell} />
              {visit ? (
                <div>
                  <span className="fw-bold">¡Ring Dong!</span>
                  <br />
                  <span>Tienes una visita</span>
                  <br />
                  <span>A {[rooms[3].bell.value]} mts</span>
                </div>
              ) : (
                <span>No tienes visitas</span>
              )}
            </div>
          </div>

          <div className="col-4">
            <button
              className="hover container-funtions d-flex align-items-center justify-content-center shadow-sm flex-column gap-1"
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
              <FontAwesomeIcon
                className="blue fs-4"
                icon={open ? faUnlockAlt : faLock}
              />
              {open ? "Cerrar" : "Abrir"}
            </button>
          </div>
        </div>

        <h2 className="fs-5 mt-4">Tus habitaciones</h2>

        <div className="row mt-4">
          {rooms.map((room, index) => (
            <div className="col-6 mb-3" key={index}>
              <button
                className={`hover container-funtions shadow-sm d-flex flex-column align-items-center justify-content-center ${
                  selectedButton === index
                    ? "btn-primary"
                    : "btn-outline-primary"
                }`}
                onClick={() => changeHabitation(index)}
              >
                <div className="w-100 text-start">
                  <span>{room.temperature ? `${room.temperature}ºC` : ""}</span>
                </div>
                {/* Si no hay un icono en iconMap, se usa el icono por defecto */}
                <FontAwesomeIcon
                  className="blue my-2 fs-1"
                  icon={iconMap[room.name] || faQuestionCircle}
                />
                <span>{room.name}</span>
              </button>
            </div>
          ))}
        </div>

        <div>
          {selectedCheckbox !== null && (
            <>
              <h3 className="fs-5">Dispositivos</h3>
              <h3 className="fs-6">{rooms[selectedCheckbox].name}</h3>
              {Object.keys(rooms[selectedCheckbox]).map((key, index) => (
                <div key={index}>
                  {key !== "name" &&
                    key !== "temperature" &&
                    key !== "door" &&
                    key !== "bell" && (
                      <div className="container-funtions mb-2">
                        {/* Primera fila: Etiqueta y Switch */}
                        <div className="row align-items-center">
                          <div className="col-8 d-flex gap-3 align-items-center">
                            {/* Icono del dispositivo */}
                            <FontAwesomeIcon
                              className="blue my-2 fs-5"
                              icon={icons[key] || faQuestionCircle}
                            />
                            {/* Etiqueta del dispositivo */}
                            <label>{key}</label>
                          </div>
                          <div className="col-4 d-flex justify-content-end">
                            {/* Switch del dispositivo */}
                            <div className="form-check form-switch">
                              <input
                                className="form-check-input fs-5"
                                role="switch"
                                type="checkbox"
                                checked={
                                  typeof rooms[selectedCheckbox][key] ===
                                  "boolean"
                                    ? rooms[selectedCheckbox][key]
                                    : rooms[selectedCheckbox][key]?.on
                                }
                                onChange={() => {
                                  const newRooms = [...rooms];
                                  if (
                                    typeof newRooms[selectedCheckbox][key] ===
                                    "boolean"
                                  ) {
                                    // Para dispositivos booleanos como waterService y gasService
                                    newRooms[selectedCheckbox][key] =
                                      !newRooms[selectedCheckbox][key];
                                  } else {
                                    // Para dispositivos con propiedades on/value
                                    const isOn =
                                      !newRooms[selectedCheckbox][key].on;
                                    newRooms[selectedCheckbox][key].on = isOn;
                                    newRooms[selectedCheckbox][key].showSlider =
                                      isOn;
                                  }
                                  setRooms(newRooms);
                                  publish(newRooms);
                                }}
                              />
                            </div>
                          </div>
                        </div>

                        {/* Fila separada: Slider */}
                        {rooms[selectedCheckbox][key]?.showSlider && (
                          <div className="row mt-2">
                            <div className="col-12">
                              <input
                                className="form-range w-100"
                                type="range"
                                min="0"
                                max="255"
                                step="51"
                                value={rooms[selectedCheckbox][key]?.value || 0}
                                onChange={(e) => {
                                  const newRooms = [...rooms];
                                  newRooms[selectedCheckbox][key].value =
                                    e.target.value;
                                  setRooms(newRooms);
                                  publish(newRooms);
                                }}
                              />
                            </div>
                          </div>
                        )}
                      </div>
                    )}
                </div>
              ))}
            </>
          )}
        </div>
      </div>
    </>
  );
}
export default App;
