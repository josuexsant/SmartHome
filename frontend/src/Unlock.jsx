import "./App.css";
import { publish } from "./helpers/client";
import { useState } from "react";
import data from "./helpers/data";
import { useNavigate } from "react-router-dom";
import "bootstrap/dist/css/bootstrap.min.css";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
  faCircleUser,
  faArrowLeft,
  faXmark,
  faRotateRight,
  faCheck,
} from "@fortawesome/free-solid-svg-icons";

function Unlock() {
  const [rooms, setRooms] = useState(data);
  const passwordDefault = "1234";
  const navigate = useNavigate();
  const [password, setPassword] = useState("");
  const [message, setMessage] = useState("");

  const handleButtonClick = (value) => {
    setPassword((prev) => prev + value);
  };

  const handleAccept = () => {
    if (password === passwordDefault) {
      const newRooms = [...rooms];
      newRooms[3].door.open = true;
      setRooms(newRooms);
      publish(newRooms);
      navigate("/");
    } else {
      setMessage("Codigo incorrecto");
      setPassword("");
    }
  };

  return (
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

      <p className="fs-6 text-center mt-5">Ingresa tu contraseña</p>
      <p>{message}</p>
      <input
        className="w-100 text-center"
        type="text"
        value={password}
        readOnly
      />
      <div className="row d-flex align-items-center justify-content-between p-5 gap-2">
        {[...Array(10).keys()].map((num) => (
          <button
            className="hover col-3 blue fw-bold container-funtions justify-content-center"
            key={num}
            onClick={() => handleButtonClick(num.toString())}
          >
            <span className="fs-2">{num}</span>
          </button>
        ))}
      </div>

      <div className="container">
        <div className="row">
          <div className="col-3">
            <button
              className="hover container-funtions d-flex justify-content-center align-items-center"
              onClick={handleAccept}
            >
              <FontAwesomeIcon className="blue fs-3" icon={faCheck} />
            </button>
          </div>
          <div className="col-3">
            <button
              className="hover container-funtions d-flex justify-content-center align-items-center"
              onClick={() => setPassword("")}
            >
              <FontAwesomeIcon className="blue fs-3" icon={faRotateRight} />
            </button>
          </div>
          <div className="col-3">
            <button
              className="hover container-funtions d-flex justify-content-center align-items-center"
              onClick={() => setPassword((prev) => prev.slice(0, -1))}
            >
              <FontAwesomeIcon className="blue fs-3" icon={faXmark} />
            </button>
          </div>
          <div className="col-3">
            <button
              className="hover container-funtions d-flex justify-content-center align-items-center"
              onClick={() => navigate("/")}
            >
              <FontAwesomeIcon className="blue fs-3" icon={faArrowLeft} />
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}

export default Unlock;
