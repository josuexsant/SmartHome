import "./App.css";
import { publish } from "./client";
import { useState } from "react";
import data from "./data";
import { useNavigate } from "react-router-dom";

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
    <div className="unlock-container">
      <h2>Ingresa tu codigo</h2>
      <p>{message}</p>
      <input type="text" value={password} readOnly />
      <div className="grid-container">
        {[...Array(10).keys()].map((num) => (
          <button key={num} onClick={() => handleButtonClick(num.toString())}>
            {num}
          </button>
        ))}
      </div>
      <button onClick={handleAccept}>Ingresar</button>
      <button onClick={() => setPassword("")}>Cancelar</button>
      <button onClick={() => setPassword((prev) => prev.slice(0, -1))}>
        Borrar
      </button>
      <button onClick={() => navigate("/")}>Regresar</button>
    </div>
  );
}

export default Unlock;
