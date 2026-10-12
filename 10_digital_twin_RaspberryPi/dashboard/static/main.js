const socket = io();

// --- Elements DOM ---
const gauge = document.getElementById("gauge");
const gaugeValue = document.getElementById("gauge-value");
const linkStatus = document.getElementById("link-status");
const mSample = document.getElementById("m-sample");
const mEkf = document.getElementById("m-ekf");
const mXgb = document.getElementById("m-xgb");
const mFinal = document.getElementById("m-final");
const mRmseEkf = document.getElementById("m-rmse-ekf");
const mRmseXgb = document.getElementById("m-rmse-xgb");
const mRmseFinal = document.getElementById("m-rmse-final");

// --- Fenetre glissante pour le graphe ---
const MAX_POINTS = 300;
const labels = [];
const dataEkf = [];
const dataXgb = [];
const dataFinal = [];

// --- Chart.js ---
const ctx = document.getElementById("socChart").getContext("2d");
const socChart = new Chart(ctx, {
  type: "line",
  data: {
    labels: labels,
    datasets: [
      {
        label: "EKF",
        data: dataEkf,
        borderColor: "#4fd1ff",
        borderWidth: 1.5,
        pointRadius: 0,
        tension: 0.1,
      },
      {
        label: "XGBoost",
        data: dataXgb,
        borderColor: "#fb923c",
        borderWidth: 1.5,
        pointRadius: 0,
        tension: 0.1,
      },
      {
        label: "Fusion",
        data: dataFinal,
        borderColor: "#e6f1ff",
        borderWidth: 2.5,
        pointRadius: 0,
        tension: 0.1,
      },
    ],
  },
  options: {
    responsive: true,
    maintainAspectRatio: false,
    animation: false,
    scales: {
      x: { ticks: { color: "#94a3b8", maxTicksLimit: 10 }, grid: { color: "#1c2735" } },
      y: {
        min: 0,
        max: 105,
        ticks: { color: "#94a3b8" },
        grid: { color: "#1c2735" },
        title: { display: true, text: "SOC (%)", color: "#94a3b8" },
      },
    },
    plugins: {
      legend: { labels: { color: "#e6f1ff" } },
    },
  },
});

// --- Jauge : couleur selon niveau de SOC ---
function gaugeColor(soc) {
  if (soc > 50) return "#12b76a";   // vert
  if (soc > 20) return "#f59e0b";   // orange
  return "#ef4444";                 // rouge
}

// --- Reception des donnees temps reel ---
socket.on("soc_update", (d) => {
  // Jauge
  gaugeValue.textContent = d.soc_final.toFixed(1) + "%";
  gauge.style.background = gaugeColor(d.soc_final);
  gauge.style.height = Math.max(40, (d.soc_final / 100) * 340) + "px";

  // Metriques live
  mSample.textContent = d.sample;
  mEkf.textContent = d.soc_ekf.toFixed(2) + "%";
  mXgb.textContent = d.soc_xgb.toFixed(2) + "%";
  mFinal.textContent = d.soc_final.toFixed(2) + "%";

  // Graphe (fenetre glissante)
  labels.push(d.sample);
  dataEkf.push(d.soc_ekf);
  dataXgb.push(d.soc_xgb);
  dataFinal.push(d.soc_final);

  if (labels.length > MAX_POINTS) {
    labels.shift();
    dataEkf.shift();
    dataXgb.shift();
    dataFinal.shift();
  }

  socChart.update("none"); // "none" = pas d'animation, plus fluide en live
});

// --- Statut de connexion TCP (PC <-> Pi) ---
socket.on("link_status", (d) => {
  if (d.connected) {
    linkStatus.textContent = "TCP: connecté (" + d.addr + ")";
    linkStatus.className = "status online";
  } else {
    linkStatus.textContent = "TCP: déconnecté";
    linkStatus.className = "status offline";
  }
});

// --- Metriques finales (RMSE vs verite terrain), a la fin du run ---
socket.on("run_finished", (m) => {
  mRmseEkf.textContent = m.rmse_ekf.toFixed(3) + "%";
  mRmseXgb.textContent = m.rmse_xgb.toFixed(3) + "%";
  mRmseFinal.textContent = m.rmse_final.toFixed(3) + "%";
});
