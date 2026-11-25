// Gerado por scripts/gerar-pagina.py; editar pipo-entrega-gelada-final.html.
#pragma once
static const char PAGINA[] = R"NEOPIPO(<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
<title>Pipo: Entrega Gelada — Aventura no Gelo</title>
<style>
:root{--bg:#070b1a;--fg:#f0f8ff;--card:#121b3b;--mut:#a6bce8;--ac:#ff7a3d;--bd:#31468c;--gold:#ffd23f;--ok:#5cf2a8;--cy:#5ce1e6;box-sizing:border-box;padding-top:env(safe-area-inset-top,0px);padding-bottom:env(safe-area-inset-bottom,0px);color-scheme:dark}
*{box-sizing:border-box}
body{margin:0;background:radial-gradient(circle at 50% 0%,#162454 0%,var(--bg) 64%);color:var(--fg);font:15px/1.4 system-ui,-apple-system,Segoe UI,Roboto,sans-serif;min-height:100vh}
main{max-width:980px;margin:0 auto;padding:10px 12px 24px}
.cab{background:linear-gradient(180deg,#1a2650 0%,#0f1734 100%);border:2px solid #384f9c;border-radius:18px;padding:10px 10px 10px;box-shadow:0 18px 46px rgba(0,0,0,.62),inset 0 1px 0 rgba(255,255,255,.12)}
.top{display:flex;align-items:center;justify-content:space-between;gap:8px;padding:0 6px 8px;flex-wrap:wrap}
.project-brand{display:flex;align-items:center;gap:14px;flex-wrap:wrap;margin:0 0 12px;padding:10px 14px;background:#f7fbff;border-radius:14px;color:#112544}.project-brand img{width:240px;height:96px;object-fit:contain;background:#081b31;border-radius:10px}.project-brand a{color:#12396b;font-weight:800;text-decoration:underline;text-underline-offset:4px;min-height:44px;display:flex;align-items:center}.project-brand strong{display:block;font-size:20px}.project-brand small{display:block;color:#314967}.brand{font:800 17px/1.1 system-ui,sans-serif;letter-spacing:.4px;color:#8ad4ff}
.brand span{color:var(--gold)}
.led-wrap{display:flex;align-items:center;gap:8px;font:700 13px/1 system-ui,sans-serif;color:#dbeaff;background:#0b1128;border:1px solid var(--bd);border-radius:999px;padding:6px 12px}
.led{width:11px;height:11px;border-radius:50%;background:var(--ok);box-shadow:0 0 8px var(--ok);transition:background .15s,box-shadow .15s;flex-shrink:0}
.led.up{background:var(--cy);box-shadow:0 0 12px var(--cy),0 0 20px var(--cy)}
.led.lost{background:#f25c78;box-shadow:0 0 10px #f25c78}

/* tela + filtro CRT sempre ligado (suavizado para máximo conforto visual 65+) */
.screen{position:relative;width:100%;aspect-ratio:320/224;background:#000;border:4px solid #090d1c;border-radius:16px;overflow:hidden;box-shadow:inset 0 0 0 2px #2e4385,0 0 28px rgba(92,225,230,.15)}
.crt-frame{position:relative;width:100%;height:100%;overflow:hidden}
canvas{display:block;width:100%;height:100%;image-rendering:pixelated;image-rendering:crisp-edges;filter:saturate(1.16) contrast(1.06) brightness(1.05)}
.crt{position:absolute;inset:0;pointer-events:none;z-index:20;border-radius:12px;
  background:
    repeating-linear-gradient(to bottom,rgba(0,0,0,.13) 0,rgba(0,0,0,.13) 1px,transparent 1px,transparent 3px),
    linear-gradient(90deg,rgba(255,40,60,.035),rgba(40,255,110,.025),rgba(40,110,255,.035)),
    radial-gradient(ellipse at 50% 50%,transparent 62%,rgba(0,0,0,.36) 100%);
  box-shadow:inset 0 0 38px rgba(0,0,0,.44),inset 0 0 8px rgba(127,200,248,.22)}
.crt::after{content:"";position:absolute;inset:0;border-radius:12px;
  background:radial-gradient(ellipse at 22% 14%,rgba(255,255,255,.07) 0%,rgba(255,255,255,.015) 28%,transparent 52%)}

/* overlays nítidos (Menu, Pausa, Fim, Pular Treino) dentro de .crt-frame -> funcionam em Tela Cheia! */
.ov{position:absolute;inset:0;z-index:10;display:none;flex-direction:column;justify-content:space-between;padding:clamp(8px,2.2%,18px);background:rgba(7,11,26,.82);backdrop-filter:blur(2px)}
.ov.show{display:flex}
.ov-head{text-align:center}
.ov-title{font:900 clamp(18px,3.6vw,34px)/1.1 system-ui,sans-serif;color:var(--gold);text-shadow:0 2px 0 #070b1a;margin:0}
.ov-rule{font:700 clamp(11px,1.75vw,16px)/1.3 system-ui,sans-serif;color:#f0f8ff;margin:4px 0 0;background:rgba(16,28,66,.9);border:1px solid #3f5bb8;border-radius:10px;padding:5px 10px;display:inline-block}
.ov-rule b.up{color:var(--gold)}
.ov-rule b.dn{color:var(--ok)}
.mgrid{display:grid;grid-template-columns:1fr 1fr;gap:clamp(6px,1.5%,12px);margin:clamp(6px,1.4%,12px) 0;flex:1;align-content:center}
.mcard{position:relative;text-align:left;padding:clamp(8px,1.8%,14px) clamp(10px,2%,16px);border-radius:14px;border:3px solid #3c54a3;background:linear-gradient(180deg,#182654 0%,#10193b 100%);color:#fff;cursor:pointer;display:flex;flex-direction:column;justify-content:center;gap:3px;min-height:0;touch-action:manipulation;transition:transform .08s,border-color .15s,box-shadow .15s}
.mcard:hover,.mcard.sel{border-color:var(--gold);box-shadow:0 0 0 2px rgba(255,210,63,.45),0 6px 18px rgba(0,0,0,.45);transform:translateY(-1px)}
.mcard.c1{border-color:#3ec98e;background:linear-gradient(180deg,#143a3a 0%,#0d272c 100%)}
.mcard.c2{border-color:#49c6e5;background:linear-gradient(180deg,#123357 0%,#0d223d 100%)}
.mcard.c3{border-color:#ff8a4c;background:linear-gradient(180deg,#47251d 0%,#2d1717 100%)}
.mcard.c4{border-color:#b27cff;background:linear-gradient(180deg,#301e59 0%,#1e133b 100%)}
.mcard.sel{border-color:var(--gold)!important}
.mcard .mt{font:800 clamp(12px,2vw,19px)/1.15 system-ui,sans-serif;color:#fff;display:flex;align-items:center;gap:6px;flex-wrap:wrap}
.mcard .md{font:600 clamp(10px,1.45vw,14px)/1.25 system-ui,sans-serif;color:#d6e7ff}
.badge{font:800 clamp(9px,1.15vw,11px)/1 system-ui,sans-serif;background:var(--gold);color:#0b1026;padding:3px 6px;border-radius:6px;margin-left:auto}
.mfoot{display:flex;align-items:center;justify-content:space-between;gap:8px;flex-wrap:wrap;background:rgba(10,16,38,.92);border:1px solid #354c96;border-radius:12px;padding:clamp(5px,1%,8px) clamp(8px,1.5%,12px);font:700 clamp(10px,1.45vw,14px)/1.2 system-ui,sans-serif}
.mfoot label{display:flex;align-items:center;gap:6px;color:#e8f6ff}
.mfoot select,.mfoot button{font:700 clamp(10px,1.4vw,13px)/1.1 system-ui,sans-serif;color:#fff;background:#182452;border:2px solid #425cb0;border-radius:8px;padding:5px 8px;min-height:0;flex:0 0 auto;cursor:pointer}
.mfoot button:hover,.mfoot select:hover{border-color:var(--gold)}
.mfoot .rec{color:var(--ok)}
.mwarn{text-align:center;font:800 clamp(11px,1.5vw,14px)/1.2 system-ui,sans-serif;color:#ff8da1;display:none}
.mwarn.show{display:block}

/* overlay de Pausa */
.ov.center{justify-content:center;align-items:center;gap:12px}
.pbox{width:min(420px,88%);background:rgba(13,20,48,.96);border:3px solid var(--cy);border-radius:16px;padding:clamp(14px,3%,22px);text-align:center;display:flex;flex-direction:column;gap:10px;box-shadow:0 16px 40px rgba(0,0,0,.65)}
.pbox h2{margin:0;font:900 clamp(18px,3vw,26px)/1.1 system-ui,sans-serif;color:var(--gold)}
.pbox p{margin:0;font:600 clamp(12px,1.6vw,15px)/1.3 system-ui,sans-serif;color:#cfe2ff}
.pbtn{width:100%;min-height:clamp(42px,7vh,54px);font:800 clamp(13px,1.9vw,17px)/1.1 system-ui,sans-serif;border-radius:12px;border:2px solid #4864bf;background:#1a285c;color:#fff;cursor:pointer;padding:8px 12px}
.pbtn.go{background:linear-gradient(180deg,#5cf2a8 0%,#2ec981 100%);color:#071915;border-color:#a2ffd0}
.pbtn.re{background:linear-gradient(180deg,#5ce1e6 0%,#2d9cc2 100%);color:#061724;border-color:#a8f3f7}
.pbtn.mn{background:linear-gradient(180deg,#ff9452 0%,#e86629 100%);color:#140a05;border-color:#ffc099}

/* botões sobre a Tela Final e botão Pular Treino */
.end-acts{position:absolute;left:50%;bottom:clamp(10px,3%,20px);transform:translateX(-50%);z-index:12;display:none;gap:10px;width:min(480px,88%)}
.end-acts.show{display:flex}
.end-acts button{flex:1;min-height:clamp(40px,7vh,52px);font:800 clamp(13px,1.8vw,16px)/1.1 system-ui,sans-serif;border-radius:12px;border:2px solid #fff;cursor:pointer;padding:8px 12px}
.skip-btn{position:absolute;bottom:12px;right:12px;z-index:12;display:none;min-height:40px;padding:8px 14px;font:800 14px system-ui,sans-serif;background:rgba(13,20,48,.94);color:var(--gold);border:2px solid var(--gold);border-radius:10px;cursor:pointer}
.skip-btn.show{display:block}

/* modo tela cheia (nativo + fallback CSS) preservando 320:224 e CRT sempre ativo */
.fs-hud,.fs-leg{display:none}
.screen:fullscreen,.screen:-webkit-full-screen,.screen.fs-fallback{position:fixed;inset:0;z-index:9999;width:100vw;height:100vh;max-width:none;aspect-ratio:auto;border:0;border-radius:0;background:#000;display:flex;align-items:center;justify-content:center}
.screen:fullscreen .crt-frame,.screen:-webkit-full-screen .crt-frame,.screen.fs-fallback .crt-frame{width:min(100vw,calc(100vh * 320 / 224));height:min(100vh,calc(100vw * 224 / 320));border-radius:0}
.screen:fullscreen .crt,.screen:-webkit-full-screen .crt,.screen.fs-fallback .crt,.screen:fullscreen .crt::after,.screen:-webkit-full-screen .crt::after,.screen.fs-fallback .crt::after{border-radius:0}
.screen:fullscreen .fs-hud,.screen:-webkit-full-screen .fs-hud,.screen.fs-fallback .fs-hud{display:flex;align-items:center;gap:8px;position:fixed;bottom:12px;right:12px;z-index:30;background:rgba(7,11,26,.88);border:2px solid #3c56a8;border-radius:12px;padding:6px 10px;backdrop-filter:blur(4px);transition:opacity .35s}
.screen.fs-idle .fs-hud{opacity:.55}
.screen .fs-hud:hover,.screen .fs-hud:focus-within{opacity:1!important}
.fs-hud button{min-height:42px;flex:0 0 auto;padding:0 12px;font:800 14px system-ui,sans-serif;border-radius:9px;background:#182452;color:#fff;border:2px solid #445eb5;cursor:pointer}
.fs-hud input[type="range"]{width:90px;accent-color:var(--cy);cursor:pointer;height:10px}
@media (pointer:coarse){
  .screen:fullscreen .fs-leg,.screen:-webkit-full-screen .fs-leg,.screen.fs-fallback .fs-leg{display:block;position:fixed;left:50%;bottom:14px;transform:translateX(-50%);z-index:25;width:min(340px,84vw);min-height:56px;opacity:.88}
}

/* barra externa simplificada para idosos (4 botões grandes + sliders grossos) */
.bar{display:flex;gap:8px;flex-wrap:wrap;margin:10px 0 8px}
.bar button{flex:1 1 138px;min-height:56px;font:800 15px/1.15 system-ui,sans-serif;color:var(--fg);background:var(--card);border:2px solid var(--bd);border-radius:12px;touch-action:none;user-select:none;-webkit-user-select:none;cursor:pointer;padding:6px 10px;transition:transform .06s,filter .1s,border-color .15s,background .15s}
.bar button:hover:not(.big){border-color:var(--cy)}
button.big{flex:2.6 1 260px;background:linear-gradient(180deg,#ff9452 0%,var(--ac) 100%);color:#0b1026;border-color:#ffb482;box-shadow:0 4px 0 #a33e12;font-size:16px}
button.big.up{background:linear-gradient(180deg,#6af7b8 0%,#2fd4a8 100%);color:#05211b;border-color:#b8ffe0;box-shadow:0 4px 0 #147a5e}
button.hold{filter:brightness(.9);transform:translateY(3px);box-shadow:0 1px 0 #a33e12}
button.glow{border-color:var(--gold)!important;box-shadow:0 0 16px rgba(255,210,63,.65);color:var(--gold)}

.audiobar{display:flex;gap:14px;flex-wrap:wrap;align-items:center;background:#0b1128;border:1px solid var(--bd);border-radius:12px;padding:10px 14px;margin:4px 0 2px}
.vol{display:flex;align-items:center;gap:10px;flex:1 1 220px;font:700 15px system-ui,sans-serif;color:#e6f2ff}
.vol input[type="range"]{flex:1;min-width:100px;accent-color:var(--cy);cursor:pointer;height:12px}
.vol input[type="range"]::-webkit-slider-thumb{width:24px;height:24px}
.vol .pct{min-width:44px;text-align:right;color:var(--gold);font:800 15px system-ui,sans-serif}
.astat{font:700 13px system-ui,sans-serif;color:var(--ok);margin-left:auto}

details.physio{margin-top:10px;background:var(--card);border:1px solid var(--bd);border-radius:10px;padding:8px 12px}
details.physio summary{cursor:pointer;font:700 13px system-ui,sans-serif;color:var(--mut);padding:4px 0;list-style:none}
details.physio summary::-webkit-details-marker{display:none}
details.physio[open] summary{color:#7fc8f8;margin-bottom:6px}
.pbar{display:flex;gap:8px;flex-wrap:wrap;align-items:center;margin:6px 0}
.pbar button{min-height:40px;font:700 13px system-ui,sans-serif;padding:0 14px;background:#192554;color:#fff;border:2px solid var(--bd);border-radius:9px;cursor:pointer}
.sensor,pre{background:#0b1026;border:1px solid var(--bd);border-radius:8px;padding:8px 10px;margin:6px 0;font:12px/1.5 monospace;white-space:pre-wrap;color:#cfe2ff}
.hint{color:var(--mut);font-size:12px;margin:6px 0 2px}
.bench{margin:12px 0;background:#0c1533;border:2px solid #405aa8;border-radius:14px;padding:14px;box-shadow:0 8px 24px #0005}
.bench h2{margin:0 0 4px;color:var(--gold);font-size:20px}.bench p{margin:4px 0 10px;color:var(--mut)}
.bench-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(190px,1fr));gap:8px}
.bench-card{background:#101b3d;border:1px solid #344b91;border-radius:10px;padding:10px;min-height:82px}
.bench-card b{display:block;color:#8ad4ff;margin-bottom:4px}.bench-card span{font:13px/1.4 monospace;overflow-wrap:anywhere}
.bench-actions{display:flex;gap:8px;flex-wrap:wrap;margin-top:10px}.bench-actions button{min-height:44px;padding:7px 14px;border-radius:9px;border:2px solid #5572c8;background:#1a285c;color:white;font-weight:800;cursor:pointer}
.bench-actions button:disabled{opacity:.5;cursor:wait}.bench-note{font:13px/1.45 monospace;color:#d8e6ff;background:#080e20;border-radius:8px;padding:9px;margin-top:8px;white-space:pre-wrap}
@media(max-width:600px){.ov{overflow-y:auto;overscroll-behavior:contain}.ov:not(.center){justify-content:flex-start;gap:8px}.ov-head,.mfoot{flex-shrink:0}.mgrid{flex:0 0 auto}.mcard{min-height:76px}}
</style>
</head>
<body>
<main>
<header class="project-brand"><img src="data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA2MDAgMjQwIiB3aWR0aD0iMTAwJSIgaGVpZ2h0PSIxMDAlIj4KICA8ZGVmcz4KICAgIDxsaW5lYXJHcmFkaWVudCBpZD0iZ3JhZFRlYWwiIHgxPSIwJSIgeTE9IjAlIiB4Mj0iMTAwJSIgeTI9IjEwMCUiPgogICAgICA8c3RvcCBvZmZzZXQ9IjAlIiBzdG9wLWNvbG9yPSIjMDZiNmQ0IiAvPgogICAgICA8c3RvcCBvZmZzZXQ9IjEwMCUiIHN0b3AtY29sb3I9IiMwMjg0YzciIC8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogICAgPGxpbmVhckdyYWRpZW50IGlkPSJncmFkQW1iZXIiIHgxPSIwJSIgeTE9IjAlIiB4Mj0iMTAwJSIgeTI9IjEwMCUiPgogICAgICA8c3RvcCBvZmZzZXQ9IjAlIiBzdG9wLWNvbG9yPSIjZmJiZjI0IiAvPgogICAgICA8c3RvcCBvZmZzZXQ9IjEwMCUiIHN0b3AtY29sb3I9IiNmNTllMGIiIC8+CiAgICA8L2xpbmVhckdyYWRpZW50PgogICAgPGZpbHRlciBpZD0ic2hhZG93IiB4PSItMTAlIiB5PSItMTAlIiB3aWR0aD0iMTIwJSIgaGVpZ2h0PSIxMjAlIj4KICAgICAgPGZlRHJvcFNoYWRvdyBkeD0iMCIgZHk9IjQiIHN0ZERldmlhdGlvbj0iNiIgZmxvb2Qtb3BhY2l0eT0iMC4xOCIvPgogICAgPC9maWx0ZXI+CiAgPC9kZWZzPgoKICA8IS0tIEZ1bmRvIEFkZXNpdm8gQXJyZWRvbmRhZG8gKE9wY2lvbmFsIHBhcmEgQ29ydGUpIC0tPgogIDxyZWN0IHg9IjEwIiB5PSIxMCIgd2lkdGg9IjU4MCIgaGVpZ2h0PSIyMjAiIHJ4PSIzNiIgZmlsbD0iIzBmMTcyYSIgZmlsdGVyPSJ1cmwoI3NoYWRvdykiIHN0cm9rZT0iIzFlMjkzYiIgc3Ryb2tlLXdpZHRoPSIzIi8+CgogIDwhLS0gU8OtbWJvbG86IE1vdmltZW50byAvIFBlZ2FkYSBEaW7Dom1pY2EgLyA1IFpvbmFzIEludGVsaWdlbnRlcyAtLT4KICA8ZyB0cmFuc2Zvcm09InRyYW5zbGF0ZSg0NSwgMzgpIj4KICAgIDwhLS0gQ8OtcmN1bG8gZXh0ZXJubyBkZSBjb25lY3RpdmlkYWRlIGRhIG1hcmNoYSAtLT4KICAgIDxjaXJjbGUgY3g9IjgwIiBjeT0iODAiIHI9IjcwIiBmaWxsPSJub25lIiBzdHJva2U9IiMxZTI5M2IiIHN0cm9rZS13aWR0aD0iNSIgc3Ryb2tlLWRhc2hhcnJheT0iMTAgOCIvPgogICAgPGNpcmNsZSBjeD0iODAiIGN5PSI4MCIgcj0iNjIiIGZpbGw9IiMxZTI5M2IiIGZpbGwtb3BhY2l0eT0iMC4zNSIvPgogICAgCiAgICA8IS0tIE7DsyBDZW50cmFsIChDZW50cm8gLSBCYXNlIFNlZ3VyYSkgLS0+CiAgICA8Y2lyY2xlIGN4PSI4MCIgY3k9IjgwIiByPSIxNCIgZmlsbD0idXJsKCNncmFkQW1iZXIpIi8+CiAgICA8Y2lyY2xlIGN4PSI4MCIgY3k9IjgwIiByPSI3IiBmaWxsPSIjZmZmZmZmIi8+CgogICAgPCEtLSA0IFpvbmFzIGVtIENydXogKEQtUGFkIEJpb2ZlZWRiYWNrKSAtLT4KICAgIDwhLS0gRnJlbnRlIC0tPgogICAgPGxpbmUgeDE9IjgwIiB5MT0iNjYiIHgyPSI4MCIgeTI9IjM0IiBzdHJva2U9IiMwNmI2ZDQiIHN0cm9rZS13aWR0aD0iNCIgc3Ryb2tlLWxpbmVjYXA9InJvdW5kIi8+CiAgICA8Y2lyY2xlIGN4PSI4MCIgY3k9IjI4IiByPSI5IiBmaWxsPSJ1cmwoI2dyYWRUZWFsKSIvPgoKICAgIDwhLS0gVHLDoXMgLS0+CiAgICA8bGluZSB4MT0iODAiIHkxPSI5NCIgeDI9IjgwIiB5Mj0iMTI2IiBzdHJva2U9IiMwNmI2ZDQiIHN0cm9rZS13aWR0aD0iNCIgc3Ryb2tlLWxpbmVjYXA9InJvdW5kIi8+CiAgICA8Y2lyY2xlIGN4PSI4MCIgY3k9IjEzMiIgcj0iOSIgZmlsbD0idXJsKCNncmFkVGVhbCkiLz4KCiAgICA8IS0tIEVzcXVlcmRhIC0tPgogICAgPGxpbmUgeDE9IjY2IiB5MT0iODAiIHgyPSIzNCIgeTI9IjgwIiBzdHJva2U9IiMwNmI2ZDQiIHN0cm9rZS13aWR0aD0iNCIgc3Ryb2tlLWxpbmVjYXA9InJvdW5kIi8+CiAgICA8Y2lyY2xlIGN4PSIyOCIgY3k9IjgwIiByPSI5IiBmaWxsPSJ1cmwoI2dyYWRUZWFsKSIvPgoKICAgIDwhLS0gRGlyZWl0YSAtLT4KICAgIDxsaW5lIHgxPSI5NCIgeTE9IjgwIiB4Mj0iMTI2IiB5Mj0iODAiIHN0cm9rZT0iIzA2YjZkNCIgc3Ryb2tlLXdpZHRoPSI0IiBzdHJva2UtbGluZWNhcD0icm91bmQiLz4KICAgIDxjaXJjbGUgY3g9IjEzMiIgY3k9IjgwIiByPSI5IiBmaWxsPSJ1cmwoI2dyYWRUZWFsKSIvPgoKICAgIDwhLS0gQXJjbyBkZSBpbXB1bHNvIGRpbsOibWljbyAoUGFzc28pIC0tPgogICAgPHBhdGggZD0iTSAzOCAxMjAgQyAyMCA4MCwgNTAgMzUsIDExMCAzMiIgZmlsbD0ibm9uZSIgc3Ryb2tlPSJ1cmwoI2dyYWRBbWJlcikiIHN0cm9rZS13aWR0aD0iNCIgc3Ryb2tlLWxpbmVjYXA9InJvdW5kIiBzdHJva2UtZGFzaGFycmF5PSI4IDYiLz4KICA8L2c+CgogIDwhLS0gVGlwb2dyYWZpYSBNT1ZBIC0tPgogIDxnIHRyYW5zZm9ybT0idHJhbnNsYXRlKDI0MCwgMTEwKSI+CiAgICA8dGV4dCBmb250LWZhbWlseT0ic3lzdGVtLXVpLCAtYXBwbGUtc3lzdGVtLCBzYW5zLXNlcmlmIiBmb250LXNpemU9Ijc2IiBmb250LXdlaWdodD0iOTAwIiBmaWxsPSIjZmZmZmZmIiBsZXR0ZXItc3BhY2luZz0iNiI+CiAgICAgIE1PVjx0c3BhbiBmaWxsPSJ1cmwoI2dyYWRBbWJlcikiPkE8L3RzcGFuPgogICAgPC90ZXh0PgogIDwvZz4KCiAgPCEtLSBTdWJ0w610dWxvIEJpb23DqWRpY28gLS0+CiAgPGcgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMjQ0LCAxNTApIj4KICAgIDx0ZXh0IGZvbnQtZmFtaWx5PSJzeXN0ZW0tdWksIC1hcHBsZS1zeXN0ZW0sIHNhbnMtc2VyaWYiIGZvbnQtc2l6ZT0iMTQiIGZvbnQtd2VpZ2h0PSI3MDAiIGZpbGw9IiMzOGJkZjgiIGxldHRlci1zcGFjaW5nPSI0Ij4KICAgICAgUElQTyDCtyBFTlRSRUdBIEdFTEFEQQogICAgPC90ZXh0PgogIDwvZz4KCiAgPCEtLSBUYWdsaW5lIFBhc3NvQ2VydG8gLS0+CiAgPGcgdHJhbnNmb3JtPSJ0cmFuc2xhdGUoMjQ0LCAxNzgpIj4KICAgIDxyZWN0IHg9IjAiIHk9IjAiIHdpZHRoPSIxMzUiIGhlaWdodD0iMjQiIHJ4PSIxMiIgZmlsbD0iIzAzNjlhMSIgZmlsbC1vcGFjaXR5PSIwLjQ1IiBzdHJva2U9IiMwMjg0YzciIHN0cm9rZS13aWR0aD0iMS41Ii8+CiAgICA8dGV4dCB4PSI2NyIgeT0iMTYiIGZvbnQtZmFtaWx5PSJzeXN0ZW0tdWksIC1hcHBsZS1zeXN0ZW0sIHNhbnMtc2VyaWYiIGZvbnQtc2l6ZT0iMTEiIGZvbnQtd2VpZ2h0PSI3MDAiIGZpbGw9IiNlMGYyZmUiIHRleHQtYW5jaG9yPSJtaWRkbGUiIGxldHRlci1zcGFjaW5nPSIxLjUiPgogICAgICBORU8gTU9WQQogICAgPC90ZXh0PgogIDwvZz4KPC9zdmc+Cg==" alt="MOVA" width="240" height="96"><div><strong>Pipo: Entrega Gelada</strong><small>Projeto de sistema ciberfísico · ESP32 + HC-SR04</small><a href="#benchPanel">Ver servidor, sensor e controles do LED ↓</a></div></header>
<div class="cab">
  <div class="top">
    <div class="brand">🐧 PIPO: <span>ENTREGA GELADA</span> · AVENTURA NO GELO</div>
    <div class="led-wrap"><span id="led" class="led"></span><span id="ledTxt">SENSOR PRONTO</span></div>
  </div>
  <div class="screen" id="scr">
    <div class="crt-frame">
      <canvas id="c" width="320" height="224"></canvas>
      <!-- Menu Principal Sênior (4 modos grandes, funciona em Tela Cheia) -->
      <div class="ov show" id="menuOv">
        <div class="ov-head">
          <h1 class="ov-title">🐧 PIPO: ENTREGA GELADA</h1>
          <div class="ov-rule"><b class="up">▲ Perna no alto</b> = Voar e pular &nbsp;·&nbsp; <b class="dn">▼ Perna no chão</b> = Descansar e pegar peixes</div>
        </div>
        <div class="mwarn" id="mWarn">⚠ Aguardando sinal do sensor... sem pressa!</div>
        <div class="mgrid" id="mGrid">
          <button class="mcard c1" data-mode="train"><span class="mt">❓ 1. COMO JOGAR <span class="badge" id="bTrain">★ 1ª VEZ</span></span><span class="md">Treino rápido de 3 passos testando a perna</span></button>
          <button class="mcard c2" data-mode="calm"><span class="mt">🐢 2. ENTREGA CALMA <span class="badge" id="bCalm">★ IDEAL</span></span><span class="md">Ritmo tranquilo · 3 fases · avisos bem antes</span></button>
          <button class="mcard c3" data-mode="normal"><span class="mt">🐧 3. AVENTURA NORMAL</span><span class="md">Ritmo mais animado · 3 fases com piruetas</span></button>
          <button class="mcard c4" data-mode="force"><span class="mt">💪 4. DESAFIO DE FORÇA</span><span class="md">Só os 3 desafios longos (&gt;15 s) com descanso</span></button>
        </div>
        <div class="mfoot">
          <label>⏱ Desafios: <select id="holdSel">
            <option value="10">10 s (Bem leve)</option>
            <option value="16" selected>16 s (Padrão)</option>
            <option value="20">20 s (Moderado)</option>
            <option value="25">25 s (Forte)</option>
            <option value="30">30 s (Avançado)</option>
          </select></label>
          <button id="hatb">🎩 Chapéu: Clássico (1/6)</button>
          <span class="rec" id="mRec">Recorde: 0 pts · 0/9 ★</span>
        </div>
      </div>
      <!-- Overlay de Pausa / Voltar ao Menu com segurança -->
      <div class="ov center" id="pauseOv">
        <div class="pbox">
          <h2>⏸ JOGO PAUSADO</h2>
          <p id="pSub">Descanse o tempo que precisar.</p>
          <button class="pbtn go" id="pResume">▶ CONTINUAR JOGO</button>
          <button class="pbtn re" id="pRestart">🔄 RECOMEÇAR ESTE MODO</button>
          <button class="pbtn mn" id="pMenu">🏠 VOLTAR AO MENU PRINCIPAL</button>
        </div>
      </div>
      <!-- Botão Pular Treino -->
      <button class="skip-btn" id="skipTrain">Pular treino ⏭</button>
      <!-- Botões grandes na Tela Final -->
      <div class="end-acts" id="endActs">
        <button class="pbtn go" id="eAgain">▶ JOGAR DE NOVO</button>
        <button class="pbtn re" id="eMenu">🏠 VOLTAR AO MENU</button>
      </div>
      <div class="crt"></div>
    </div>
    <!-- Mini HUD de Tela Cheia (canto inferior direito, nunca some completamente) -->
    <div class="fs-hud">
      <button id="fsMenu" title="Pausa / Menu (P)">⏸ Menu</button>
      <button id="fsMute" title="Som (M)">🔊</button>
      <input id="fsVol" type="range" min="0" max="100" value="70" aria-label="Volume da música">
      <button id="fsExit" title="Sair da tela cheia (F / Esc)">✕ Sair</button>
    </div>
    <button id="fsLeg" class="big fs-leg">▲ SEGURE = LEVANTAR PERNA</button>
  </div>
  <audio id="bgm" preload="auto" loop><source src="/audio.ogg" type="audio/ogg"></audio>
  <div class="bar">
    <button id="leg" class="big">▲ SEGURE = LEVANTAR PERNA</button>
    <button id="menuBtn">▶ COMEÇAR</button>
    <button id="fsb">⛶ TELA CHEIA</button>
    <button id="snb">🔊 SOM LIGADO</button>
  </div>
  <div class="audiobar">
    <label class="vol">🎵 Música <input id="volBgm" type="range" min="0" max="100" value="70"><span id="volBgmTxt" class="pct">70%</span></label>
    <label class="vol">🔔 Efeitos <input id="volSfx" type="range" min="0" max="100" value="35"><span id="volSfxTxt" class="pct">35%</span></label>
    <span class="astat" id="astat">🎵 Carregando música...</span>
  </div>
</div>
<section class="bench" id="benchPanel" aria-live="polite">
  <h2>🔧 Bancada do projeto: quem faz o quê</h2>
  <p>Este navegador é o cliente HTTP. O ESP32 é o servidor em <code>192.168.4.1:80</code> e cria a rede Wi-Fi. O celular/computador cliente recebe um IP DHCP próprio (normalmente <code>192.168.4.x</code>; confira nos detalhes da rede Wi-Fi). Os dados abaixo vêm da placa quando a página é aberta pelo endereço do servidor.</p>
  <div class="bench-grid">
    <div class="bench-card"><b>1 · Cliente navegador</b><span id="benchClient">Verificando origem…</span></div>
    <div class="bench-card"><b>2 · Servidor ESP32 / HTTP</b><span id="benchServer">Aguardando consulta…</span></div>
    <div class="bench-card"><b>3 · Sensor HC-SR04</b><span id="benchSensor">Aguardando leitura…</span></div>
    <div class="bench-card"><b>4 · Atuador LED</b><span id="benchLed">Aguardando estado…</span></div>
  </div>
  <div class="bench-actions"><button data-led="ligar">Comandar LED: ligar</button><button data-led="desligar">Comandar LED: desligar</button><button data-led="automatico">LED em modo automático</button></div>
  <div class="bench-note" id="benchLog">A tela registra status, leitura e resposta HTTP. O comando de LED só é habilitado quando a página vem do servidor ESP32.</div>
</section>
<details class="physio" id="physBox">
  <summary>⚙ Métricas da sessão e diagnóstico do sensor (dados do protótipo; não são avaliação clínica)</summary>
  <div class="pbar"><button id="inv">SINAL INVÁLIDO (segure para testar)</button></div>
  <div class="pbar"><button id="exportMetrics">⬇ Baixar métricas desta sessão (JSON)</button></div>
  <div class="sensor" id="sensor"></div>
  <pre id="m"></pre>
  <p class="hint">Atalhos: Espaço = perna · 1/2/3/4 ou setas+Enter = escolher modo · P = Pausa/Menu · F = Tela Cheia · C = Chapéu · M = Som · I = Sinal inválido. O jogo simula o HC-SR04 até receber distâncias reais por <code>window.pipoSensor(mm)</code>. Amostras aceitas: 50–600 mm; histerese 280/320 mm; confirmação após 2 amostras. O percentual de quadros é medido pelo navegador; não representa FPS do ESP32.</p>
</details>
</main>
<script>
const cv=document.getElementById('c'),cx=cv.getContext('2d');cx.imageSmoothingEnabled=false;
const N='#0b1026',B1='#1c2a5e',B2='#3a5fb0',IC='#7fc8f8',W='#f0f8ff',O='#ff7a3d',Y='#ffd23f',P='#f25c78',G1='#9aa3b8',AU='#5cf2a8',WA='#1f64db',WB='#11378f',SP='#060814',PR='#9b6bff',CY='#5ce1e6',GN='#38d996',RD='#e84a5f';
const HZ=84,GY=196,MINHOP=.8,WAIT_MAX=24;

/* perfis de ritmo sênior (Calmo = padrão acessível 65+; Normal = mais animado) */
const PACE={
  calm:{cruise:56,slow:44,canal:50,fever:60,grace:.60,holdGrace:1.15,nearH:190,urgH:115,nearR:175,nearA:165,curvScale:.55,flip:false},
  normal:{cruise:74,slow:54,canal:60,fever:78,grace:.48,holdGrace:.90,nearH:165,urgH:90,nearR:150,nearA:145,curvScale:1,flip:true},
  force:{cruise:58,slow:48,canal:52,fever:60,grace:.60,holdGrace:1.05,nearH:175,urgH:105,nearR:160,nearA:155,curvScale:.4,flip:false}
};
let gameMode='calm';
const cfg=()=>PACE[gameMode]||PACE.calm;

const R=(x,y,w,h,c)=>{cx.fillStyle=c;cx.fillRect(Math.round(x),Math.round(y),Math.round(w),Math.round(h))};
function T(s,x,y,c,sz,al,out){
  cx.font='bold '+(sz||11)+'px monospace';cx.textAlign=al||'center';cx.fillStyle=N;
  if(out){for(const [dx,dy] of [[-1.5,0],[1.5,0],[0,-1.5],[0,1.5],[1.5,1.5]])cx.fillText(s,x+dx,y+dy)}
  else cx.fillText(s,x+1,y+1);
  cx.fillStyle=c||W;cx.fillText(s,x,y);
}
const pick=a=>a[Math.random()*a.length|0];
const dec=v=>v.toFixed(1).replace('.',',');
const mmss=v=>{v=Math.round(v);return Math.floor(v/60)+':'+String(v%60).padStart(2,'0')};
const clamp=(v,a,b)=>Math.max(a,Math.min(b,v));

/* ===== áudio: trilha videoplayback + SFX suaves independentes ===== */
const AC=window.AudioContext||window.webkitAudioContext;
const bgm=document.getElementById('bgm');
let ac=null,mute=false,sfxG=null,sfxF=null,noiseBuf=null,audioReady=false,bgmVol=.7,sfxVol=.35,curBgmVol=.7;
try{
  const vb=localStorage.getItem('pipoVolBgm'),vs=localStorage.getItem('pipoVolSfx'),vm=localStorage.getItem('pipoMute');
  if(vb!==null)bgmVol=clamp(+vb,0,1);
  if(vs!==null)sfxVol=clamp(+vs,0,1);
  if(vm==='1')mute=true;
}catch(e){}
curBgmVol=bgmVol;
const PENTA=[523.25,587.33,659.25,783.99,880,1046.5,1174.66,1318.51];
function syncBgmPlay(){
  if(!bgm)return;
  const shouldPlay=audioReady&&!mute&&bgmVol>.005&&st!=='pause'&&st!=='lost';
  if(shouldPlay){
    if(bgm.paused){try{const pr=bgm.play();if(pr&&pr.catch)pr.catch(()=>{})}catch(e){}}
  }else{
    if(!bgm.paused){try{bgm.pause()}catch(e){}}
  }
}
function unlock(){
  audioReady=true;
  try{
    if(!ac){
      ac=new AC();sfxF=ac.createBiquadFilter();sfxF.type='lowpass';sfxF.frequency.value=2600;
      sfxG=ac.createGain();sfxG.gain.value=sfxVol;sfxF.connect(sfxG);sfxG.connect(ac.destination);
      const len=ac.sampleRate*.22;noiseBuf=ac.createBuffer(1,len,ac.sampleRate);
      const d=noiseBuf.getChannelData(0);for(let i=0;i<len;i++)d[i]=Math.random()*2-1;
    }
    if(ac.state==='suspended')ac.resume();
  }catch(e){}
  syncBgmPlay();
}
function snd(f1,f2,d,ty,v,dl){
  if(mute||sfxVol<=.005||!ac||!sfxF)return;
  try{
    const o=ac.createOscillator(),g=ac.createGain(),n=ac.currentTime+(dl||0);
    o.type=(ty==='sine'||ty==='triangle')?ty:'triangle';
    o.frequency.setValueAtTime(Math.max(55,f1),n);
    o.frequency.exponentialRampToValueAtTime(Math.max(55,f2),n+d);
    const amp=(v||.05)*1.4;
    g.gain.setValueAtTime(.0001,n);g.gain.linearRampToValueAtTime(amp,n+.008);
    g.gain.exponentialRampToValueAtTime(.0001,n+d);
    o.connect(g);g.connect(sfxF);o.start(n);o.stop(n+d+.01);
  }catch(e){}
}
function whoosh(d,f0,f1,v){
  if(mute||sfxVol<=.005||!ac||!noiseBuf||!sfxF)return;
  try{
    const s=ac.createBufferSource(),f=ac.createBiquadFilter(),g=ac.createGain(),n=ac.currentTime;
    s.buffer=noiseBuf;f.type='bandpass';f.frequency.setValueAtTime(f0,n);f.frequency.exponentialRampToValueAtTime(f1,n+d);
    g.gain.setValueAtTime((v||.04)*.9,n);g.gain.exponentialRampToValueAtTime(.0001,n+d);
    s.connect(f);f.connect(g);g.connect(sfxF);s.start(n);s.stop(n+d);
  }catch(e){}
}
function jingle(ns,d){ns.forEach((f,i)=>snd(f,f*1.005,d*.95,'triangle',.05,i*d))}
function musicTick(dt){
  if(!bgm)return;
  syncBgmPlay();
  const duck=st==='fly'&&fl&&fl.ph==='air'&&!fl.up;
  const tg=mute?0:(duck?bgmVol*.42:bgmVol);
  curBgmVol+=(tg-curBgmVol)*Math.min(1,dt*6);
  try{bgm.volume=clamp(curBgmVol,0,1)}catch(e){}
}

/* ===== sensor HC-SR04 (simulado ou ESP32 via window.pipoSensor) ===== */
let legKey=false,legBtn=false,invKey=false,invBtn=false,legPhys=0,hist=[{t:0,v:0}],tChange=0,extSensor=false;
function setLeg(){const v=+(legKey||legBtn);if(v!==legPhys){legPhys=v;tChange=performance.now();hist.push({t:tChange,v});if(hist.length>60)hist.shift()}}
function legAt(t0){for(let i=hist.length-1;i>=0;i--)if(hist[i].t<=t0)return hist[i].v;return 0}
let cand=0,candN=0,conf=0,invRun=0,okRun=0,sigOK=true,dist=400,prev='run';
const M={tot:0,val:0,eps:0,trans:0,lat:0,free:0,hOk:0,hTot:0,replays:0,up:0,cur:0,longest:0,holds:[],cOk:0,cTot:0,flips:0,maxCombo:0,gulls:0};
function feedDist(mm,now){
  M.tot++;dist=mm;
  if(dist<50||dist>600){invRun++;okRun=0;if(invRun>=2&&sigOK){sigOK=false;M.eps++;onLost()}return}
  M.val++;invRun=0;okRun++;
  if(!sigOK&&okRun>=2){sigOK=true;onRegain()}
  const c=dist<=280?1:dist>=320?0:cand;
  if(c===cand)candN++;else{cand=c;candN=1}
  if(candN>=2&&cand!==conf){conf=cand;M.trans++;onConf(conf,now)}
}
function sample(){
  if(extSensor)return;
  const now=performance.now();
  const mm=(invKey||invBtn||Math.random()<.02)?0:((legAt(now-100)?200:400)+Math.round(Math.random()*30-15));
  feedDist(mm,now);
}
window.pipoSensor=mm=>{extSensor=true;feedDist(Number(mm)||0,performance.now())};
/* As consultas têm prazo para detectar falha e retomar sem recarregar a página. */
const isBoard=location.protocol==='http:'&&location.hostname==='192.168.4.1';
async function boardJson(path,options={}){
 const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),2000);
 try{const r=await fetch(path,{...options,cache:'no-store',signal:controller.signal});
 if(!r.ok)throw Error(`HTTP ${r.status}`);return {data:await r.json(),status:r.status};}
 finally{clearTimeout(timer)}
}
/* Painel de demonstração: cliente -> servidor HTTP do ESP32 -> sensor/atuador. */
(()=>{
 const client=document.getElementById('benchClient'),server=document.getElementById('benchServer'),sensor=document.getElementById('benchSensor'),ledState=document.getElementById('benchLed'),log=document.getElementById('benchLog');
 let connected=false,busy=false;
 const buttons=[...document.querySelectorAll('[data-led]')];
 function controls(){buttons.forEach(b=>{b.disabled=!isBoard||!connected||busy})}
 client.textContent=`Navegador ${navigator.userAgent.match(/(Chrome|Firefox|Safari|Edg)\/?[\d.]*/)?.[0]||''} · CLIENTE HTTP · IP DHCP do dispositivo (ver Wi-Fi) · acessando ${location.host}`;
 buttons.forEach(b=>{b.addEventListener('click',async()=>{
 busy=true;controls();log.textContent=`POST /api/led {"modo":"${b.dataset.led}"} · enviando…`;
 try{const {data:j,status}=await boardJson('/api/led',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({modo:b.dataset.led})});
 render(j);log.textContent=`POST /api/led · HTTP ${status} · modo ${j.led.modo} confirmado pelo servidor · ${new Date().toLocaleTimeString()}`;}
 catch(e){log.textContent=`Comando sem confirmação: ${e.message}. Consulte o estado antes de repetir.`;offline(e)}
 finally{busy=false;controls()}
 })});
 function render(j){
 if(j?.origem!=='ESP32'||!j.sensor||!j.led||typeof j.led.ligado!=='boolean')throw Error('Resposta de status inválida');
 connected=true;controls();const s=j.sensor;
 server.textContent=`${j.origem} · SERVIDOR HTTP ${location.host} · uptime ${j.uptime_ms??'?'} ms · boot ${j.boot_id||'?'}`;
 sensor.textContent=s.valido?`VÁLIDO · ${s.distancia_cm} cm · amostra ${s.idade_ms??'?'} ms`:`SEM ECO VÁLIDO · distância indisponível${s.idade_ms!=null?` · última amostra ${s.idade_ms} ms`:''}`;
 ledState.textContent=`modo ${j.led.modo} · saída comandada ${j.led.ligado?'LIGADA':'DESLIGADA'} · conferir LED físico`;
 }
 function offline(e){connected=false;controls();server.textContent=`ESP32 indisponível · ${e.message}`;sensor.textContent='Sem leitura atual confirmada';ledState.textContent='Estado atual não confirmado';}
 async function poll(){
 if(!isBoard){server.textContent='Sem conexão com ESP32 · abra http://192.168.4.1/ conectado à rede NEO-MOVA';sensor.textContent='Simulado nesta prévia; não é uma leitura física';ledState.textContent='Sem comando físico · controles desabilitados';controls();return}
 try{const {data}=await boardJson('/api/status');render(data)}catch(e){offline(e)}
 finally{setTimeout(poll,1000)}
 }
 controls();poll();
})();
/* Na placa, nunca gerar entradas simuladas, mesmo antes da primeira resposta. */
if(isBoard){
 extSensor=true;sigOK=false;dist=0;
 const lerSensorReal=async()=>{
   try{const {data:s}=await boardJson('/api/sensor');
     const valid=s.valido===true&&Number.isFinite(s.distancia_cm)&&Number.isFinite(s.idade_ms)&&s.idade_ms<=250;
     window.pipoSensor(valid?s.distancia_cm*10:0)}
   catch(e){window.pipoSensor(0);window.pipoSensor(0)}
   finally{setTimeout(lerSensorReal,100)}
 };
 lerSensorReal();
}
setInterval(sample,71);
function onConf(c,now){
  if(c!==1)return;
  hopT=MINHOP;M.lat=extSensor?0:Math.round(now-tChange);
  if(st==='run'||st==='train'){sqX=.84;sqY=1.22;snd(300,720,.14,'triangle',.045);if(st==='run'&&!reasonUp(210))M.free++}
}
function onLost(){
  if(st==='run'||st==='rest'||st==='fly'||st==='train'||st==='forceRest'){prev=st;st='lost'}
  else if(st==='resume'){st='lost'}
}
function onRegain(){if(st==='lost'){st='resume';resT=1.5}}

/* ===== chapéus desbloqueáveis (auto-equipa na hora!) ===== */
const HATS=[
  {id:'classic',name:'Clássico',req:'Inicial'},
  {id:'pirate',name:'Pirata',req:'Roube 1 gaivota ou termine 1 partida'},
  {id:'shades',name:'Óculos 80s',req:'Ative a Festa da Aurora'},
  {id:'tophat',name:'Cartola Kraken',req:'Vença o Capitão Kraken'},
  {id:'crown',name:'Coroa Real',req:'Ganhe medalha Prata ou Ouro'},
  {id:'astro',name:'Astro Ouro',req:'Complete 1 desafio longo sem soltar'}
];
let unlocked=new Set(['classic']),curHat='classic',newHatMsg='',hatGlowT=0;
let trained=false;
try{
  const s=localStorage.getItem('pipoHats');if(s)JSON.parse(s).forEach(x=>unlocked.add(x));
  const h0=localStorage.getItem('pipoHat');if(h0&&unlocked.has(h0))curHat=h0;
  trained=localStorage.getItem('pipoTrained')==='1';
}catch(e){}
function saveHats(){try{localStorage.setItem('pipoHats',JSON.stringify([...unlocked]));localStorage.setItem('pipoHat',curHat)}catch(e){}}
function unlockHat(id){
  if(unlocked.has(id))return;unlocked.add(id);curHat=id;saveHats();
  const h0=HATS.find(x=>x.id===id);if(!h0)return;
  newHatMsg='NOVO CHAPÉU: '+h0.name.toUpperCase()+'!';hatGlowT=2.2;
  pop('CHAPÉU: '+h0.name.toUpperCase()+'!',160,92,Y);spark(pipoX(),170-h,22,[Y,W,AU]);
  jingle([587,784,988,1175],.07);updateHatBtn();
}
function nextHat(){
  const list=HATS.filter(x=>unlocked.has(x.id));
  const i=(list.findIndex(x=>x.id===curHat)+1)%list.length;
  curHat=list[i].id;saveHats();updateHatBtn();snd(660,990,.09,'triangle',.05);
}
function updateHatBtn(){
  const b=document.getElementById('hatb'),h0=HATS.find(x=>x.id===curHat)||HATS[0];
  if(b){b.textContent='🎩 Chapéu: '+h0.name+' ('+unlocked.size+'/'+HATS.length+')';b.classList.toggle('glow',hatGlowT>0)}
}

/* ===== 3 biomas + 3 desafios longos (>15 s) em português claro e acolhedor ===== */
const BIOMES=[
  {name:'PÔR-DO-SOL POLAR',sky:['#1e1342','#5e235c','#c44953','#f58f49'],road:[IC,'#4476cf'],side:['#181842','#272158'],edge:W,prop:'pine',client:'VOVÓ MORSA'},
  {name:'AURORA NEON',sky:['#070c22','#0c173d','#14255c','#1e3775'],road:[CY,'#284fa8'],side:['#0a1029','#131e4a'],edge:AU,prop:'crystal',client:'DJ URSO'},
  {name:'ROTA ESTELAR',sky:['#120624','#2c0d42','#57184a','#8f2544'],road:[PR,'#3a2978'],side:['#17092b','#261142'],edge:O,prop:'volcano',client:'REI PINGUIM'}
];
const EV={
  kite:{name:'SUPER-PIPA',cue:'SUPER-PIPA CHEGANDO!',wait:'LEVANTE PARA VOAR NA PIPA!',go:'PIPA NO AR! FUJA DA NEVE!',back:'MUITO BEM! DE VOLTA AO AR!',
    perf:'AVALANCHE VENCIDA!',done:'ESCAPOU DA NEVE!',to:'PIPO POUSOU!',
    acts:['FUGINDO DA BOLA DE NEVE!','GAIVOTAS NA COLA!','CÉU BRILHANDO NA AURORA!','QUASE CHEGANDO!'],col:AU},
  whale:{name:'JATO DA BALEIA',cue:'BALEIA AMIGA CHEGANDO!',wait:'LEVANTE PARA SUBIR NA BALEIA!',go:'NO JATO! ACERTE O KRAKEN!',back:'ISSO! JATO NO MÁXIMO!',
    perf:'KRAKEN VENCIDO!',done:'KRAKEN ESPANTADO!',to:'A BALEIA MERGULHOU!',
    acts:['CAPITÃO KRAKEN CHEGOU!','BOLHAS NA CARTOLA DELE!','BALEIA DE ÓCULOS ESCUROS!','MEGA-ESGUICHO FINAL!'],col:CY},
  rocket:{name:'FOGUETE POLAR',cue:'FOGUETE CHEGANDO!',wait:'LEVANTE PARA LIGAR O FOGUETE!',go:'DECOLOU! PEGA O DISCO!',back:'FOGUETE LIGADO DE NOVO!',
    perf:'CAMPEÃO DAS ESTRELAS!',done:'CHEGOU NAS ESTRELAS!',to:'POUSO SEGURO!',
    acts:['DISCO VOADOR NA FRENTE!','LADO A LADO NAS NUVENS!','ULTRAPASSOU O DISCO!','CHEGADA NAS ESTRELAS!'],col:O}
};
const LONG_K={K:'kite',B:'whale',R:'rocket'};
const FORCE_SEQ=['kite','whale','rocket'];

/* ===== fases (largada tranquila + 3 biomas + 2 eventos >15 s por fase) ===== */
const NEED_AIR=new Set(['gate','puf','gold','gull','airf','ramp','walrus']);
const RT='.....ff..ff..ff..ff..ff..ff..ff..ff.....';
const LV=[
 '.........fffff....^....ffff....G.....fff....aaaF....m....ffff....g....fff.....'+'w'.repeat(12)+'.....ffff.....K'+RT+'G.....ffff....^....fff....p....aaaF.....B'+RT+'....G....^....fffff',
 '.........ffff....m....ffff....G....^....fff...aaaF....g....ffff.....'+'='.repeat(15)+'.....fff....G....ffff.....B'+RT+'p....fff....^....G....g....ffff....aaaF.....R'+RT+'....G....p....ffff....F',
 '.........ffff....^....G....ffff....m....fff....g....aaaF....ffff.....'+'='.repeat(16)+'.....ffff....G.....K'+RT+'p....ffff.....'+'w'.repeat(12)+'.....^....fff....aaaF.....R'+RT+'....G....m....ffff....F'];

let st='menu',p=0,sc=0,spd=56,leg=0,fish=0,totFish=0,score=0,hopT=0,h=0,wasAir=false;
let bumpT=0,happyT=0,feverT=0,feverPts=0,hitStop=0,flipA=0,wasFlip=false,restBonus=0,sqX=1,sqY=1,curv=0,hzNow=HZ;
let restT=0,resT=0,t=0,objs=[],cans=[],longs=[],pend=[],parts=[],bubs=[],pops=[],legEnd=0,legStart=0,avail=1,stars=[0,0,0],played=false;
let flyer=null,cam=null,seal=null,walPop=null,shk=0,evT=13,combo=0,inC=null,lastC=null,swim=false,fl=null,sf=[],aur=0,idleUp=0;
let perfN=0,okN=0,gGot=0,gAv=1,tip='',snow=[],actShown=-1,bossHit=0,hatBounce=0,krakenFly=0,dingDone=false,banner=null;
let ghosts=[],shots=[],grindT=0,grindNote=0,endT=0,endDisp=0,stamped=false,endTick=0,bestScore=0,best=0;
let train=null,forceIdx=0,forceRestT=0,menuIdx=0;
try{best=+localStorage.getItem('pipoBest')||0;bestScore=+localStorage.getItem('pipoScore')||0}catch(e){}
let holdBase=16;try{holdBase=+localStorage.getItem('pipoHold')||16}catch(e){}
const holdFor=l=>holdBase+2*l;
const isAir=()=>conf===1||hopT>0;
for(let i=0;i<32;i++)snow.push({x:Math.random()*320,y:Math.random()*224,v:18+Math.random()*28,sz:Math.random()<.3?2:1});

function flyAct(){
  if(!fl)return 0;
  const left=fl.need-fl.got,fr=fl.got/Math.max(1,fl.need);
  if(left<=5||fr>=.75)return 3;
  return fr>=.5?2:fr>=.25?1:0;
}
function curveAt(pos){
  if(st==='rest'||st==='train'||st==='forceRest')return 0;
  if(st==='fly'&&fl&&(fl.kind==='whale'||fl.kind==='rocket'))return 0;
  return (Math.sin(pos*.0022)*42+Math.sin(pos*.0051)*16)*(st==='menu'?.65:cfg().curvScale);
}
function xOf(s){return 160+curv*(1-s)*(1-s)}
function pipoX(){
  if(st==='fly'&&fl&&fl.kind==='kite')return 198;
  if(st==='run')return Math.round(160-curv*.11);
  return 160;
}
function reasonUp(r){return !!inC||pend.length>0||objs.some(o=>!o.done&&(NEED_AIR.has(o.k)||o.k==='long')&&o.p-p<r&&o.p-p>-20)||cans.some(c=>c.p-p<r&&c.p+c.len>p)}
function showBanner(l){const bm=BIOMES[l];banner={t:2.1,text:'FASE '+(l+1)+' · '+bm.name}}

function gen(l){
  const b=p,s=LV[l];legStart=b;objs=[];pend=[];avail=0;perfN=0;okN=0;gGot=0;gAv=[...s].filter(c=>c==='f').length;
  for(let i=0;i<s.length;i++){
    const c=s[i],at=b+i*20;
    if(c==='w'||c==='='){
      let j=i;while(s[j]===c)j++;const n=j-i,rail=c==='=';
      objs.push({k:'canal',rail,p:at,len:n*20,wet:false,done:false});
      for(let k=0;k<n;k++)objs.push({k:'wf',rail,p:at+k*20+10,done:false});
      avail+=n+(rail?4:3);i=j-1;continue;
    }
    if(LONG_K[c]){objs.push({k:'long',kind:LONG_K[c],p:at,done:false});avail+=Math.round(holdFor(l)*2.4+8);continue}
    const k={f:'fish',a:'airf',F:'gold',p:'puf',G:'gate',g:'gull','^':'ramp',m:'walrus'}[c];if(!k)continue;
    objs.push({k,p:at,done:false});avail+=c==='f'||c==='a'?1:c==='F'||c==='m'?3:c==='g'?2:c==='^'?5:0;
  }
  cans=objs.filter(o=>o.k==='canal');longs=objs.filter(o=>o.k==='long');inC=lastC=null;swim=false;
  legEnd=b+s.length*20+80;showBanner(l);
}
function resetRunVars(){
  p=0;sc=0;spd=cfg().cruise;leg=0;fish=0;totFish=0;score=0;hopT=0;h=0;wasAir=false;bumpT=0;happyT=0;feverT=0;feverPts=0;hitStop=0;
  flipA=0;wasFlip=false;restBonus=0;sqX=1;sqY=1;combo=0;parts=[];bubs=[];pops=[];ghosts=[];shots=[];sf=[];fl=null;
  stars=[0,0,0];evT=13;idleUp=0;tip='';newHatMsg='';walPop=null;endT=0;endDisp=0;stamped=false;banner=null;train=null;forceIdx=0;forceRestT=0;
  Object.assign(M,{holds:[],up:0,cur:0,longest:0,hOk:0,hTot:0,cOk:0,cTot:0,free:0,flips:0,maxCombo:0,gulls:0});
}
function startMode(mode){
  unlock();
  if(!sigOK)return;
  if(mode==='train'){
    gameMode='calm';resetRunVars();
    train={step:0,prog:0,doneT:0,fishes:[{d:180},{d:230},{d:280}]};
    st='train';snd(440,660,.14,'triangle');syncOverlays();return;
  }
  if(played)M.replays++;played=true;
  gameMode=mode||'calm';resetRunVars();
  if(gameMode==='force'){
    forceIdx=0;leg=0;
    startFly(FORCE_SEQ[0],holdFor(0));
  }else{
    gen(0);st='run';snd(440,880,.14,'triangle');
  }
  syncOverlays();
}
/* compatibilidade com start() direto */
function start(){startMode(gameMode==='force'?'force':gameMode)}
function goMenu(){
  fl=null;sf=[];shots=[];bubs=[];pops=[];pend=[];train=null;banner=null;feverT=0;h=0;st='menu';
  syncOverlays();
}
function finishSession(){
  st='end';bubs=[];pops=[];fl=null;sf=[];shots=[];endT=0;endDisp=0;stamped=false;
  const tot=stars.reduce((a,b)=>a+b,0),rk=getRank();
  unlockHat('pirate');if(rk.tier>=2)unlockHat('crown');
  if(gameMode!=='force'&&tot>best){best=tot;try{localStorage.setItem('pipoBest',best)}catch(e){}}
  if(score>bestScore){bestScore=score;try{localStorage.setItem('pipoScore',bestScore)}catch(e){}}
  syncOverlays();
}

function say(s,x,y){bubs=bubs.filter(b=>b.y!==y);bubs.push({s,x,y,t:2.2})}
function pop(s,x,y,c){pops.push({s,x,y,c:c||Y,t:1.1})}
function spark(x,y,n,cols){for(let i=0;i<n;i++)parts.push({x,y,vx:(Math.random()-.5)*110,vy:-Math.random()*100-15,l:.7,c:cols[i%cols.length],g:200})}
function addFever(pts){
  if(st!=='run'||feverT>0)return;
  feverPts+=pts;
  if(feverPts>=12){
    feverPts=0;feverT=8;happyT=2;shk=.22;hitStop=.035;
    pop('FESTA DA AURORA! ×2',160,112,Y);spark(pipoX(),165-h,24,[Y,AU,CY,P,O]);
    jingle([523,659,784,1047,1319],.065);unlockHat('shades');
  }
}
function addCombo(){combo++;if(combo>M.maxCombo)M.maxCombo=combo}
function gain(n,silentPop){
  const mult=feverT>0&&st==='run'?2:1,amt=n*mult;
  fish+=amt;totFish+=amt;score+=amt*100;addCombo();
  const f0=PENTA[combo%PENTA.length];snd(f0,f0*1.1,.08,'triangle',.045);
  spark(pipoX(),172-h,amt>1?10:4,mult>1?[Y,AU,W]:amt>1?[Y,W]:[Y]);
  if(!silentPop){const px=st==='fly'?pipoX()-48+(Math.random()-.5)*12:pipoX()+(Math.random()-.5)*18;pop('+'+amt+(mult>1?'★':''),px,174-h,mult>1?AU:amt>1?Y:W)}
}
function bump(){bumpT=1.1;combo=0;feverPts=Math.max(0,feverPts-3);const l=Math.min(fish,2);fish-=l;shk=.25;spark(pipoX(),180,l*3+6,[Y,W]);snd(160,70,.24,'triangle',.07);pop('Opa! Sem problema!',160,136,W)}
function win(o,late){
  if(o.k==='gate'){
    M.hTot++;M.hOk++;addCombo();
    if(feverT>0){
      fish+=5;totFish+=5;score+=600;shk=.22;hitStop=.035;spark(pipoX(),170-h,22,[Y,O,P,W]);
      jingle([659,880,1319],.05);pop('SUPER SALTO! +5',pipoX(),142-h,O);
    }else{
      score+=250;addFever(2);spark(pipoX(),190,16,[Y,W,IC]);snd(520,960,.12,'triangle');
      pop(late?'UFA!':'PULOU!',pipoX(),150-h,IC);
    }
  }else if(o.k==='puf'){M.hTot++;M.hOk++;score+=150;addCombo();addFever(2);snd(780,1120,.07,'triangle');if(late||Math.random()<.4)pop('BOA!',pipoX(),150-h,AU)}
  else if(o.k==='ramp'){
    M.flips++;if(cfg().flip){flipA=.01;wasFlip=true}else{sqX=.82;sqY=1.24}
    hopT=Math.max(hopT,1.15);hitStop=.035;shk=.15;happyT=1.4;
    gain(5,true);score+=400;addFever(4);pop(cfg().flip?'PIRUETA NO AR! +5':'SALTO LINDO! +5',pipoX(),138-h,Y);spark(pipoX(),175-h,20,[Y,O,AU,W]);
    whoosh(.22,700,2400,.05);jingle([587,784,1047,1319],.055);
  }else if(o.k==='walrus'){
    hopT=Math.max(hopT,1.05);sqX=.8;sqY=1.26;hitStop=.03;happyT=1;walPop={x:pipoX(),y:192,t:.8};
    gain(3,true);score+=250;addFever(3);pop('PULO NA MORSA! +3',pipoX(),145-h,CY);spark(pipoX(),182,14,[CY,W,Y]);
    snd(200,640,.2,'triangle',.08);
  }else if(o.k==='airf'){gain(1);addFever(1)}
  else if(o.k==='gold'){gain(3);addFever(3);happyT=.9;pop('PEIXE DOURADO! +3',pipoX(),142-h,Y)}
  else{M.gulls++;hitStop=.035;shk=.14;gain(2);addFever(3);happyT=.9;flyer={x:pipoX(),y:150,f:false};unlockHat('pirate');pop('PEGOU O PEIXE! +2',pipoX(),142-h,Y)}
}
function lose(o){
  if(feverT>0&&o.k==='puf'){
    M.hTot++;M.hOk++;hitStop=.035;shk=.2;gain(3,true);pop('ESCUDO! +3',pipoX(),145-h,AU);
    spark(pipoX(),175,18,[AU,Y,W]);snd(300,880,.15,'triangle',.06);return;
  }
  if(o.k==='gate'){M.hTot++;bump()}
  else if(o.k==='puf'){M.hTot++;combo=0;fish=Math.max(0,fish-1);bumpT=.6;snd(180,85,.18,'triangle');spark(pipoX(),175,6,[P,W]);pop('Ui!',pipoX(),150-h,P)}
  else if(o.k==='gull'){flyer={x:pipoX(),y:150,f:true}}
}
function startFly(kind,customNeed){
  const m=EV[kind],ready=conf===1;actShown=-1;bossHit=0;hatBounce=0;krakenFly=0;dingDone=false;shots=[];
  fl={kind,need:customNeed||holdFor(leg),got:0,run:0,best:0,drops:0,el:0,ph:ready?'air':'wait',down:0,up:ready,sec:0,mark:0,fishT:0,lt:0,shotT:.45,msg:ready?m.go:m.wait,msgT:2.6};
  sf=[];pend=[];bubs=[];st='fly';
  snd(ready?400:320,ready?1200:900,.3,'triangle',.06);
}
function landFly(ok,msg){
  const f=fl;M.holds.push({kind:f.kind,need:f.need,best:f.best,drops:f.drops,ok});
  f.ph='land';f.lt=0;f.msg=msg;f.msgT=3.2;
}
function completeFly(){
  const f=fl,m=EV[f.kind],perfect=f.drops===0;let n=0;
  for(const q of sf)n+=q.g?3:1;sf=[];shots=[];
  const bonus=(perfect?8:4)+n;fish+=bonus;totFish+=bonus;score+=bonus*150+(perfect?1500:700);
  okN++;if(perfect){perfN++;unlockHat('astro')}
  if(f.kind==='whale'){unlockHat('tophat');krakenFly=.01}
  happyT=2.4;hitStop=.05;shk=.32;
  spark(pipoX(),100,36,[Y,W,AU,P,O,CY]);pop((perfect?'PERFEITO! +':'VENCEU! +')+bonus,160,104,Y);
  jingle(perfect?[523,659,784,1047,1319]:[523,659,784,1047],.1);
  landFly(true,perfect?m.perf:m.done);
}

/* ===== loop de atualização ===== */
function update(dt){
  t+=dt;musicTick(dt);
  if(hatGlowT>0){hatGlowT-=dt;if(hatGlowT<=0)updateHatBtn()}
  if(banner){banner.t-=dt;if(banner.t<=0)banner=null}
  if(hitStop>0){hitStop-=dt;return}
  if(hopT>0)hopT-=dt;if(bumpT>0)bumpT-=dt;if(happyT>0)happyT-=dt;if(feverT>0)feverT-=dt;
  if(shk>0)shk-=dt;if(bossHit>0)bossHit-=dt;if(hatBounce>0)hatBounce=Math.max(0,hatBounce-dt*45);
  if(krakenFly>0){krakenFly+=dt;if(!dingDone&&krakenFly>=1.45){dingDone=true;snd(1560,2340,.22,'sine',.06);spark(240,40,14,[Y,W,CY])}if(krakenFly>2.4)krakenFly=0}
  if(flipA>0){flipA+=dt*8.4;if(flipA>=Math.PI*2){flipA=0;if(wasFlip){wasFlip=false;jingle([880,1175,1568],.045)}}}
  sqX+=(1-sqX)*Math.min(1,dt*12);sqY+=(1-sqY)*Math.min(1,dt*12);
  parts.forEach(q=>{q.x+=q.vx*dt;q.y+=q.vy*dt;q.vy+=q.g*dt;q.l-=dt});parts=parts.filter(q=>q.l>0);
  bubs.forEach(b=>b.t-=dt);bubs=bubs.filter(b=>b.t>0);
  pops.forEach(q=>{q.y-=22*dt;q.t-=dt});pops=pops.filter(q=>q.t>0);
  ghosts.forEach(g=>g.l-=dt);ghosts=ghosts.filter(g=>g.l>0);
  shots.forEach(s=>{s.x+=(s.tx-s.x)*Math.min(1,dt*7);s.y+=s.vy*dt;s.l-=dt;if(s.y<=s.ty){s.l=0;bossHit=.22;hatBounce=10;pop('ACERTOU!',s.tx,s.ty-10,Y);spark(s.tx,s.ty,8,[CY,Y,W])}});
  shots=shots.filter(s=>s.l>0);
  if(flyer){flyer.x+=105*dt;flyer.y-=58*dt;if(flyer.x>340)flyer=null}
  if(cam){cam.x+=70*dt;if(cam.x>350)cam=null}
  if(seal){seal.t-=dt;if(seal.t<=0)seal=null}
  if(walPop){walPop.y+=28*dt;walPop.t-=dt;if(walPop.t<=0)walPop=null}
  snow.forEach(q=>{q.y+=q.v*dt;q.x-=curv*.35*dt;if(q.y>224){q.y=-2;q.x=Math.random()*320}if(q.x<0)q.x+=320;if(q.x>320)q.x-=320});

  if(st==='menu'||st==='end'){
    sc+=32*dt;curv+=(curveAt(sc)-curv)*Math.min(1,dt*3);hzNow+=(HZ+Math.sin(sc*.003)*3-hzNow)*Math.min(1,dt*3);
    h=Math.max(0,h-120*dt);aur=Math.max(0,aur-dt*.3);
    if(st==='end'){
      endT+=dt;const fr=clamp(endT/.85,0,1);endDisp=Math.round(score*fr);
      if(fr<1){endTick-=dt;if(endTick<=0){endTick=.07;snd(520+fr*400,540+fr*400,.03,'triangle',.03)}}
      else if(!stamped){stamped=true;shk=.22;spark(266,44,24,[Y,AU,CY,P,W]);jingle([523,659,784,1047,1319],.09)}
      if(Math.random()<.22)parts.push({x:Math.random()*320,y:-4,vx:(Math.random()-.5)*35,vy:36+Math.random()*35,l:2.4,c:pick([Y,AU,CY,P,O,W]),g:18});
    }
    return;
  }
  if(st==='resume'){resT-=dt;if(resT<=0){st=prev;syncOverlays()}}
  if(st==='run'||st==='fly'||st==='train'){if(conf===1){M.up+=dt;M.cur+=dt;if(M.cur>M.longest)M.longest=M.cur}else M.cur=0}
  if(st==='train')trainStep(dt);
  else if(st==='run')runStep(dt);
  else if(st==='fly')flyStep(dt);
  else if(st==='rest')restStep(dt);
  else if(st==='forceRest')forceRestStep(dt);

  curv+=(curveAt(p)-curv)*Math.min(1,dt*3.5);
  const hzTg=(st==='run'?HZ+Math.sin(p*.0032)*4*cfg().curvScale:HZ);hzNow+=(hzTg-hzNow)*Math.min(1,dt*3);
  if(st==='run'||st==='fly'||st==='rest'||st==='train'||st==='forceRest'){
    let tg=0,down=145;
    if(st==='fly'&&fl){if(fl.ph==='air'&&fl.up)tg=fl.kind==='whale'?50:68;down=fl.ph==='land'?34:46}
    else if((st==='run'||st==='train')&&isAir())tg=flipA>0?54:inC?40:38;
    const airNow=tg>4;if(wasAir&&!airNow&&(st==='run'||st==='train')){sqX=1.2;sqY=.82;spark(pipoX(),202,6,[W,IC])}
    wasAir=airNow;
    h+=tg>h?Math.min(tg-h,235*dt):-Math.min(h-tg,down*dt);
  }
  if((flipA>0||feverT>0)&&st==='run'&&Math.random()<.45){
    ghosts.push({x:pipoX(),y:Math.round(200-h),a:flipA,c:feverT>0?Y:CY,l:.2});
  }
  const at=st==='fly'&&fl&&fl.ph!=='wait'?.35+.65*Math.min(1,fl.got/fl.need):0;
  aur+=(at-aur)*Math.min(1,dt*1.5);
}

/* === Treino Guiado Interativo de 3 Passos === */
function trainStep(dt){
  const tr=train;sc+=40*dt;
  if(tr.doneT>0){
    tr.doneT-=dt;
    if(tr.doneT<=0){
      if(tr.step>=2){
        trained=true;try{localStorage.setItem('pipoTrained','1')}catch(e){}
        startMode('calm');return;
      }
      tr.step++;tr.prog=0;
      if(tr.step===1)tr.fishes=[{d:110},{d:165},{d:220}];
    }
    return;
  }
  if(tr.step===0){
    if(conf===1){tr.prog+=dt;if(tr.prog>=.6){tr.doneT=1.8;happyT=1.5;spark(160,150,20,[Y,AU,W]);jingle([523,659,784],.08)}}
  }else if(tr.step===1){
    for(const q of tr.fishes){q.d-=48*dt;if(q.d<=0){q.d=240;if(conf===0){gain(1);tr.prog++}}}
    if(conf===0&&tr.prog>=3){tr.doneT=1.8;happyT=1.5;spark(160,170,20,[Y,AU,W]);jingle([523,659,784],.08)}
  }else{
    if(conf===1){tr.prog+=dt;if(tr.prog>=3){tr.doneT=2.2;happyT=2;spark(160,140,32,[Y,AU,CY,W]);jingle([523,659,784,1047],.09)}}
    else tr.prog=Math.max(0,tr.prog-dt*.4);
  }
}

/* === Descanso Guiado entre séries no Modo Desafio de Força === */
function forceRestStep(dt){
  sc+=36*dt;forceRestT-=dt;
  if(Math.random()<.05&&conf===0)spark(160,185,2,[AU,W]);
  if(forceRestT<=0){
    forceIdx++;leg=Math.min(2,forceIdx);
    if(forceIdx>=FORCE_SEQ.length){finishSession()}
    else{startFly(FORCE_SEQ[forceIdx],holdFor(forceIdx))}
  }
}

function runStep(dt){
  const a=isAir(),px=pipoX(),C=cfg();
  inC=cans.find(c=>p>=c.p&&p<c.p+c.len)||null;
  if(inC!==lastC){
    if(lastC){
      M.cTot++;swim=false;grindNote=0;
      if(!lastC.wet){
        const b=lastC.rail?4:3;M.cOk++;fish+=b;totFish+=b;score+=b*150;addFever(4);happyT=1.1;
        spark(px,180,18,[Y,AU,CY,W]);pop((lastC.rail?'TRILHO COMPLETO! +':'CANAL SECO! +')+b,px,148-h,AU);
        jingle([660,880,1175],.07);
      }
    }
    if(inC)grindT=0;
    lastC=inC;
  }
  if(inC){
    if(!a)inC.gt=(inC.gt||0)+dt;else inC.gt=0;
    if(!a&&!swim&&inC.gt>C.grace){swim=true;inC.wet=true;combo=0;spark(px,200,12,[W,IC]);snd(200,90,.28,'triangle',.06);pop('Água gelada!',px,160,IC)}
    else if(a&&swim){swim=false;snd(340,860,.18,'triangle');pop('Voltou pro ar!',px,155-h,AU)}
    if(a&&inC.rail){
      const py=Math.round(200-h);
      if(Math.random()<.55)parts.push({x:px+(Math.random()-.5)*14,y:py+1,vx:(Math.random()-.5)*90,vy:12+Math.random()*30,l:.3,c:pick([Y,CY,W,AU]),g:140});
      grindT-=dt;if(grindT<=0){grindT=.28;const f0=PENTA[grindNote++%PENTA.length];snd(f0,f0*1.06,.07,'triangle',.03)}
    }
  }
  idleUp=(conf===1&&!reasonUp(220))?idleUp+dt:0;
  const nearHaz=Math.min(999,...objs.filter(o=>!o.done&&(o.k==='gate'||o.k==='puf')).map(o=>o.p-p));
  const nearC=cans.some(c=>c.p+c.len>p&&c.p-p<90);
  const tgtSpd=nearHaz<125&&!a?C.slow:nearC?C.canal:feverT>0?C.fever:C.cruise;
  spd+=(tgtSpd-spd)*Math.min(1,dt*4.5);p+=spd*dt;sc+=spd*dt;
  if(!a&&Math.abs(curv)>14&&Math.random()<.4)parts.push({x:px+(curv>0?-8:8),y:200,vx:(curv>0?-35:35)+(Math.random()-.5)*14,vy:-12-Math.random()*18,l:.32,c:W,g:100});
  evT-=dt;
  if(evT<=0&&!a&&!reasonUp(280)){
    evT=14+Math.random()*8;const e=pick(['rain','ufo','seal']);
    if(e==='rain'){fish+=4;totFish+=4;score+=400;pop('CHUVA DE PEIXES! +4',160,132,Y);for(let i=0;i<16;i++)parts.push({x:115+Math.random()*90,y:-4,vx:0,vy:Math.random()*42,l:1.3,c:Y,g:130});snd(1100,620,.32,'triangle')}
    else if(e==='ufo'){cam={x:-30,y:44}}
    else{seal={t:3.6};snd(500,320,.14,'triangle')}
  }
  if(a&&h>4&&!(inC&&inC.rail))parts.push({x:px+(Math.random()-.5)*10,y:204-h,vx:(Math.random()-.5)*26,vy:28,l:.28,c:feverT>0?pick([Y,AU,CY,P,O]):inC?CY:W,g:0});
  for(const o of objs){
    if(o.done||o.p>p)continue;o.done=true;
    if(o.k==='fish'){
      if(!a){
        gain(1);gGot++;restBonus++;
        if(restBonus>=8){restBonus=0;fish+=2;totFish+=2;score+=200;pop('BOM DESCANSO! +2',px,148,AU);snd(580,880,.12,'triangle',.05)}
      }
    }
    else if(o.k==='wf'){if(a)gain(1)}
    else if(NEED_AIR.has(o.k)){if(a)win(o,false);else pend.push({o,t:C.grace})}
    else if(o.k==='long'){startFly(o.kind);return}
  }
  for(const q of pend){q.t-=dt;if(isAir()){win(q.o,true);q.x=1}else if(q.t<=0){lose(q.o);q.x=1}}
  pend=pend.filter(q=>!q.x);
  if(p>=legEnd){stars[leg]=rate();bubs=[];pops=[];st='rest';restT=0;h=0;feverT=0;snd(350,880,.26,'triangle')}
}
function rate(){
  const r=fish/Math.max(1,avail),g=gGot/Math.max(1,gAv),s=r>=.7&&perfN>0&&g>=.55?3:r>=.45&&okN>0&&g>=.3?2:1;
  tip=s===3?'':okN===0?'Dica: segure nos desafios longos!':g<.3?'Dica: abaixe a perna para descansar!':perfN===0?'Dica: tente segurar 1 desafio sem soltar!':g<.55?'Dica: pegue peixes no chão e descanse!':'Dica: pegue mais peixes no caminho!';
  return s;
}
function flyStep(dt){
  const f=fl,m=EV[f.kind],C=cfg();f.el+=dt;if(f.msgT>0)f.msgT-=dt;
  const act=flyAct(),px=pipoX();
  spd+=((f.ph==='air'?(f.kind==='rocket'?96:80)+act*6:f.ph==='wait'?22:48)-spd)*Math.min(1,dt*2);sc+=spd*dt;
  if(f.ph==='wait'){
    if(conf===1){f.ph='air';f.el=0;f.up=true;f.msg=m.go;f.msgT=2.4;snd(400,1200,.3,'triangle',.06)}
    else if(f.el>WAIT_MAX)landFly(false,'TUDO BEM! VAMOS CONTINUAR!');
    return;
  }
  if(f.ph==='air'){
    if(conf===1){f.down=0;if(!f.up){f.up=true;f.msg=m.back;f.msgT=2;snd(420,980,.18,'triangle',.06)}}
    else{f.down+=dt;if(f.up&&f.down>=C.holdGrace){f.up=false;f.drops++;f.run=0;f.mark=0;combo=0;f.msg='DESCANSE E LEVANTE DE NOVO!';f.msgT=2.6;snd(280,140,.22,'triangle',.05)}}
    if(f.up){
      f.got+=dt;f.run+=dt;if(f.run>f.best)f.best=f.run;
      if(act>actShown){actShown=act;f.msg=m.acts[act];f.msgT=2.5;if(act>0){shk=.16;spark(px,140,12,[Y,m.col,W]);jingle([523+act*70,659+act*70,784+act*70],.06)}}
      if(f.kind==='kite'){
        parts.push({x:330,y:28+Math.random()*155,vx:-260,vy:0,l:1.1,c:act>=2?pick([AU,Y,W]):W,g:0});
      }else if(f.kind==='whale'){
        if(Math.random()<.5)parts.push({x:160+(Math.random()-.5)*22,y:200-h+2,vx:(Math.random()-.5)*65,vy:-18-Math.random()*30,l:.55,c:act>=2?pick([Y,CY,AU,P]):W,g:130});
        f.shotT-=dt;if(f.shotT<=0&&act>=1){
          f.shotT=act>=3?.36:.66;const kx=160+Math.sin(t*2.0)*50;
          shots.push({x:160,y:170-h,tx:kx,ty:74,vy:-220,l:.6});snd(540+act*80,860+act*80,.06,'triangle',.035);
        }
      }else{
        parts.push({x:160+(Math.random()-.5)*14,y:204-h,vx:(Math.random()-.5)*24,vy:130+Math.random()*50,l:.42,c:pick([Y,O,P,W]),g:0});
        if(Math.random()<.55)parts.push({x:Math.random()*320,y:-2,vx:0,vy:230+act*25,l:.9,c:Math.random()<.25?Y:W,g:0});
      }
      const mk=Math.floor(f.run/5);
      if(mk>f.mark&&f.got<f.need-.8){
        f.mark=mk;const ms=mk*5;fish+=2;totFish+=2;score+=300;happyT=.9;
        pop(ms+'s FIRME! +2',f.kind==='kite'?246:236,162-h,AU);spark(px,166-h,14,[AU,Y,W]);jingle([587,784,988],.06);
      }
    }
    const s=Math.floor(f.got);
    if(s>f.sec){f.sec=s;const left=f.need-s;if(left>0&&left<=5)snd(520+(6-left)*95,550+(6-left)*95,.1,'triangle',.05)}
    f.fishT-=dt;if(f.fishT<=0){f.fishT=.52;sf.push({d:260,g:Math.random()<.16||act>=2})}
    for(const q of sf){q.d-=spd*dt;if(q.d<=0){q.x=1;if(f.up)gain(q.g?3:1)}}
    sf=sf.filter(q=>!q.x);
    if(f.got>=f.need)completeFly();
    else if(f.el>f.need*2+18)landFly(false,m.to);
  }else if(f.ph==='land'){
    f.lt+=dt;
    if(f.lt>=3.0){
      fl=null;sf=[];shots=[];
      if(gameMode==='force'){
        if(forceIdx>=FORCE_SEQ.length-1){finishSession()}
        else{pops=[];st='forceRest';forceRestT=12;h=0}
      }else{st='run'}
    }
  }
}
/* Medalhas universais (fáceis de entender para idosos!) */
function getRank(){
  if(gameMode==='force'){
    const ok=M.holds.filter(x=>x.ok).length,perf=M.holds.filter(x=>x.ok&&x.drops===0).length;
    if(perf>=3)return{r:'OURO ★',tier:4,c:Y,title:'FORÇA INCRÍVEL! 3 DE 3 SEM SOLTAR!'};
    if(ok>=3)return{r:'OURO',tier:3,c:AU,title:'EXCELENTE! VENCEU OS 3 DESAFIOS!'};
    if(ok>=2)return{r:'PRATA',tier:2,c:CY,title:'MUITO BEM! ÓTIMO TREINO DE FORÇA!'};
    return{r:'BRONZE',tier:1,c:O,title:'BOM TREINO! CONTINUE PRATICANDO!'};
  }
  const tot=stars.reduce((a,b)=>a+b,0),allPerf=M.holds.length>=6&&M.holds.every(x=>x.ok&&x.drops===0);
  if(tot===9&&allPerf)return{r:'OURO ★',tier:4,c:Y,title:'CAMPEÃO DO CORREIO GELADO!'};
  if(tot>=8)return{r:'OURO',tier:3,c:AU,title:'PARABÉNS! ENTREGA EXCELENTE!'};
  if(tot>=6)return{r:'PRATA',tier:2,c:CY,title:'MUITO BEM! ÓTIMA ENTREGA!'};
  return{r:'BRONZE',tier:1,c:O,title:'VALEU! BOM EXERCÍCIO HOJE!'};
}
function restStep(dt){
  spd*=Math.pow(.04,dt);p+=spd*dt;sc+=spd*dt;const before=restT;restT+=dt;
  if(restT>1.3&&restT<3.1&&Math.random()<.3)spark(160,148,1,[Y,W]);
  if(before<3.1&&restT>=3.1){
    snd(160,80,.3,'triangle',.07);const s=stars[leg];
    const lines=[
      s===3?'QUENTINHO! FIZ UM GORRO!':s===2?'DELÍCIA, MEU NETO!':'OBRIGADA, PIPO!',
      s===3?'SOLTA O SOM! SHOW TOTAL!':s===2?'MANDOU BEM NO RITMO!':'BOA! PRÓXIMA MÚSICA!',
      s===3?'VIDA LONGA AO CORREIO!':s===2?'APROVADO PELO TRONO!':'BOM SERVIÇO, PIPO!'
    ];
    say(lines[leg],160,76);
    if(s===3){spark(160,104,22,[Y,W,P,AU,CY]);jingle([523,659,784,1047],.08)}
  }
  if(leg===2&&restT>3.2&&Math.random()<.08)spark(70+Math.random()*180,45+Math.random()*35,12,[Y,P,AU,CY,O]);
  if(restT>=9.0){
    leg++;fish=0;combo=0;tip='';restBonus=0;feverPts=0;
    if(leg>2){finishSession()}
    else{gen(leg);st='run'}
  }
}

/* ===== desenho (320×224 pixel art com fontes ≥ 10px e Semáforo Único) ===== */
const sk=Array.from({length:44},()=>({x:Math.random()*320|0,y:Math.random()*76|0,ph:Math.random()*6}));
function drawSky(mode){
  const bm=BIOMES[st==='menu'||st==='end'||st==='train'?0:Math.min(2,leg)];
  const rk=mode==='fly'&&fl&&fl.kind==='rocket';
  if(rk&&aur>.25){
    R(0,0,320,hzNow+4,SP);
    for(const s of sk){const sy=(s.y+t*115*(.4+aur))%(hzNow+2);R(s.x,sy,1,Math.max(1,Math.round(aur*6)),s.ph>3?Y:s.ph>1.5?W:CY)}
  }else{
    const bands=bm.sky,bh=Math.ceil((hzNow+4)/bands.length);
    bands.forEach((c,i)=>R(0,i*bh,320,bh+1,c));
    for(const s of sk)if((leg>0||s.y<34)&&Math.sin(t*3+s.ph)>-.45)R((s.x-curv*.4+320)%320,s.y,1,1,s.ph>3?Y:W);
    if(bm===BIOMES[0]&&!(mode==='fly'&&fl&&fl.kind==='whale')){
      const sx=160-curv*.7,sy=hzNow-22;
      R(sx-18,sy-12,36,24,Y);R(sx-22,sy-8,44,16,Y);R(sx-14,sy-16,28,32,Y);
      R(sx-20,sy+2,40,3,O);R(sx-18,sy+7,36,3,O);R(sx-14,sy+12,28,2,P);
    }
    const auA=(bm===BIOMES[1]?.6:0)+(mode==='fly'&&fl&&fl.kind==='kite'?aur*.95:0);
    if(auA>.05){
      cx.globalAlpha=Math.min(.85,auA);
      for(let x=0;x<320;x+=2){
        const y0=12+Math.sin(x*.03+t*.9)*7+Math.sin(x*.012-t*.6)*6,hh=12+Math.sin(x*.05+t*1.4)*6;
        R(x,y0,2,hh,(x>>3)&1?AU:CY);R(x,y0+hh,2,3,PR);
      }
      cx.globalAlpha=1;
    }
  }
  if(mode==='fly'&&fl&&fl.kind==='whale'&&aur>.05){
    cx.globalAlpha=Math.min(.92,aur);
    R(280,48,16,16,W);R(282,46,12,20,W);R(278,50,20,12,W);R(283,51,3,3,IC);R(290,56,3,3,IC);
    cx.globalAlpha=1;
  }
  if(rk&&aur>.15){
    const px=286+Math.sin(t*.3)*5,py=56;cx.globalAlpha=Math.min(1,aur);
    R(px-7,py-7,14,14,PR);R(px-5,py-9,10,18,PR);R(px-4,py-5,5,4,IC);
    R(px-13,py-1,26,3,Y);R(px-10,py+2,20,2,O);cx.globalAlpha=1;
  }
  if(!(rk&&aur>.55)){
    const shift=Math.round(-curv*.5);
    for(let y=hzNow-42;y<=hzNow;y++){
      const k=(y-(hzNow-42))/42,xe=k*148;
      R(0,y,Math.max(0,xe+shift),1,bm.side[0]);R(Math.min(320,320-xe+shift),y,320,1,bm.side[0]);
      R(xe+shift-2,y,2,1,bm.edge);R(320-xe+shift,y,2,1,bm.edge);
    }
    if(bm===BIOMES[2])for(const vx of [64+shift,256+shift]){R(vx-8,hzNow-28,16,4,O);R(vx-5,hzNow-31,10,3,Y)}
  }
}
function drawProp(x,y,s,type){
  const w=Math.max(2,8*s),h0=Math.max(4,36*s);
  if(type==='pine'){
    R(x-w*.2,y-h0*.3,w*.4,h0*.3,'#6b3f2b');
    R(x-w*.9,y-h0*.65,w*1.8,h0*.4,'#1c6b5a');R(x-w*.65,y-h0*.9,w*1.3,h0*.35,'#268a73');R(x-w*.4,y-h0,w*.8,h0*.2,W);
  }else if(type==='crystal'){
    R(x-w*.45,y-h0,w*.9,h0,CY);R(x-w*.2,y-h0*1.12,w*.4,h0*.25,W);R(x+w*.15,y-h0*.7,w*.45,h0*.7,PR);
  }else{
    R(x-w*.5,y-h0*.8,w,h0*.8,'#3a2054');R(x-w*.35,y-h0*.95,w*.7,h0*.22,O);R(x-w*.2,y-h0*1.05,w*.4,h0*.15,Y);
  }
}
function ground(mode){
  const bm=BIOMES[st==='menu'||st==='end'||st==='train'?0:Math.min(2,leg)];
  const whaleMode=mode==='fly'&&fl&&fl.kind==='whale',rkMode=mode==='fly'&&fl&&fl.kind==='rocket'&&aur>.4;
  for(let y=Math.round(hzNow)+1;y<224;y++){
    const s=(y-hzNow)/(GY-hzNow),d=60/s-60,s2=Math.floor((sc+d)/30)&1,hw=90*s,wp=p+d,xc=xOf(s);
    const wet=whaleMode||(mode==='run'&&cans.some(c=>wp>=c.p&&wp<c.p+c.len));
    R(0,y,320,1,rkMode?(s2?SP:N):bm.side[s2]);
    if(wet){
      R(xc-hw,y,hw*2,1,(Math.floor((whaleMode?sc+d:wp)/12+t*4)&1)?WA:WB);
      if((y+Math.floor(t*10))%5===0)R(xc-hw+((y*53+Math.floor(t*30))%Math.max(1,hw*2|0)),y,Math.max(3,hw/8),1,W);
    }else{
      const rc=feverT>0&&st==='run'?(s2?Y:AU):rkMode?(s2?B1:B2):bm.road[s2];
      R(xc-hw,y,hw*2,1,rc);
    }
    const ec=feverT>0&&st==='run'?O:rkMode?PR:bm.edge;
    R(xc-hw-2,y,2,1,ec);R(xc+hw,y,2,1,ec);
  }
  for(let k=Math.ceil(sc/90);k*90<sc+260;k++){
    const d=k*90-sc,s=60/(60+d),y=hzNow+(GY-hzNow)*s,hw=90*s,xc=xOf(s);
    drawProp(xc-hw-14*s,y,s,bm.prop);drawProp(xc+hw+14*s,y,s,bm.prop);
  }
  if(mode==='run'){
    for(const c of cans){
      if(c.rail){
        const d0=Math.max(0,c.p-p),d1=Math.min(255,c.p+c.len-p);
        if(d1>d0){
          for(let d=d1;d>=d0;d-=10){
            const s=60/(60+d),y=hzNow+(GY-hzNow)*s,xc=xOf(s),q=lvl(s);
            R(xc-4*q,y-40*q,8*q,5*q,CY);R(xc-2*q,y-39*q,4*q,3*q,W);
            if(Math.round(d)%30<10)R(xc-1*q,y-35*q,2*q,35*q,B2);
          }
        }
      }
      const d=c.p-p;if(d<0||d>=260)continue;
      const s=60/(60+d),y=hzNow+(GY-hzNow)*s,hw=90*s,xc=xOf(s),q=lvl(s),bw=Math.max(3,7*q),bh=Math.max(4,10*q);
      for(const sx of [xc-hw+2*q,xc+hw-bw-2*q]){R(sx,y-bh,bw,bh,c.rail?CY:O);R(sx,y-bh,bw,Math.max(2,3*q),Y)}
    }
  }
}
const lvl=s=>s>.85?1:s>.58?.65:s>.4?.45:s>.27?.3:.2;
function upArrow(xc,y,q){if(q<.35)return;const dy=Math.round(Math.sin(t*10)*3);T('↑',xc,y+dy,Y,Math.max(10,Math.round(13*q)),null,1)}
function fishS(x,y,q,c){const w=12*q,h0=6*q;R(x-w/2,y-h0*1.3,w,h0,c);R(x+w/2,y-h0*1.6,w*.35,h0*1.5,c);R(x-w/3,y-h0*1.1,Math.max(1,q*2),Math.max(1,q*2),N)}
function puff(x,y,q){R(x-6*q,y-10*q,12*q,8*q,P);R(x-4*q,y-12*q,8*q,12*q,P);[[-8,-7],[6,-7],[-1,-14],[-1,0]].forEach(a=>R(x+a[0]*q,y+a[1]*q,2*q,2*q,W));R(x-3*q,y-8*q,2*q,2*q,N)}
function gateS(xc,y,q,s){
  const hw=90*s,H=34*q,bl=Math.sin(t*12)>0;
  R(xc-hw,y-H,hw*2,H,IC);R(xc-hw,y-H,hw*2,Math.max(2,4*q),W);R(xc-hw,y-3*q,hw*2,3*q,B2);
  for(let i=1;i<4;i++)R(xc-hw+hw*2*i/4,y-H+6*q,Math.max(1,2*q),H*.6,W);
  R(xc-hw+2*q,y-H-5*q,7*q,5*q,bl?P:Y);R(xc+hw-9*q,y-H-5*q,7*q,5*q,bl?P:Y);
  upArrow(xc,y-H-8*q,q);
}
function rampS(xc,y,q){
  const w=26*q,h0=16*q;
  for(let i=0;i<6;i++){const f=i/6;R(xc-w/2+f*2,y-h0*f-3*q,w-f*4,3*q,i&1?O:Y)}
  R(xc-w/2,y-2*q,w,2*q,W);upArrow(xc,y-h0-8*q,q);
}
function walrusS(xc,y,q,shock){
  R(xc-14*q,y-11*q,28*q,11*q,'#7c6c82');R(xc-10*q,y-16*q,20*q,6*q,'#96849e');
  if(shock){R(xc-6*q,y-15*q,4*q,4*q,W);R(xc+2*q,y-15*q,4*q,4*q,W);R(xc-5*q,y-14*q,2*q,2*q,N);R(xc+3*q,y-14*q,2*q,2*q,N);T('!?',xc,y-22*q,Y,10,null,1)}
  else{R(xc-4*q,y-13*q,2*q,2*q,N);R(xc+2*q,y-13*q,2*q,2*q,N);upArrow(xc,y-20*q,q)}
  R(xc-4*q,y-9*q,2*q,5*q,W);R(xc+2*q,y-9*q,2*q,5*q,W);
}
function gullS(x,y,q,fl0){
  const w=Math.sin(t*16)>0?-3:3;
  R(x-7*q,y-5*q,14*q,6*q,W);R(x-16*q,y-5*q+w*q,10*q,2*q,W);R(x+6*q,y-5*q+w*q,10*q,2*q,W);
  R(x+5*q,y-9*q,7*q,6*q,W);R(x+12*q,y-6*q,4*q,2*q,O);R(x+8*q,y-8*q,2*q,2*q,N);R(x+4*q,y-11*q,9*q,3*q,N);
  if(fl0)R(x+14*q,y-5*q,5*q,3*q,Y);
}
function kiteS(x,y,q,gold){
  const H=16*q;
  for(let i=0;i<H;i++){const w=(i<H*.4?i/(H*.4):(H-i)/(H*.6))*10*q;R(x-w,y+i,w*2,1,gold?Y:(i<H*.4?O:Y))}
  R(x-Math.max(1,q)/2,y,Math.max(1,q),H,N);R(x-8*q,y+H*.4,16*q,Math.max(1,q),N);
  for(let k=1;k<5;k++)R(x+Math.sin(t*5+k)*4*q-2*q,y+H+k*5*q,4*q,2*q,k&1?P:CY);
}
function whaleIcon(x,y,q){
  R(x-16*q,y-10*q,32*q,12*q,B2);R(x-12*q,y-13*q,24*q,4*q,B2);R(x-10*q,y-2*q,20*q,4*q,IC);
  R(x-23*q,y-11*q,8*q,4*q,B2);R(x+8*q,y-8*q,3*q,3*q,W);R(x+9*q,y-7*q,2*q,2*q,N);
  R(x-2*q,y-24*q,4*q,11*q,IC);R(x-7*q,y-27*q,14*q,4*q,W);
}
function rocketIcon(x,y,q){
  R(x-6*q,y-24*q,12*q,18*q,W);R(x-4*q,y-30*q,8*q,6*q,P);R(x-2*q,y-33*q,4*q,3*q,P);
  R(x-3*q,y-20*q,6*q,6*q,IC);R(x-10*q,y-12*q,4*q,8*q,O);R(x+6*q,y-12*q,4*q,8*q,O);R(x-4*q,y-6*q,8*q,4*q,Y);
}
function drawAvalanche(act,fr){
  const bx=fl.ph==='land'?72:(fl.up?82:108)+Math.sin(t*5)*3,by=fl.ph==='land'?152:146+Math.sin(t*9)*3;
  const sz=fl.ph==='land'?24:22+Math.min(10,fr*8)+(!fl.up?6:0);
  R(bx-sz,by-sz,sz*2,sz*2,W);R(bx-sz+4,by-sz-4,sz*2-8,sz*2+8,W);R(bx-sz-4,by-sz+4,sz*2+8,sz*2-8,IC);
  R(bx-sz+6,by-sz+2,sz*1.3,sz*1.3,W);
  if(fl.ph==='land'){T('@ @',bx,by+2,N,10);R(bx-5,by+7,10,3,O)}
  else{
    const off=Math.round(Math.sin(t*7)*4);
    R(bx-8+off,by-7,6,6,N);R(bx+4+off,by-7,6,6,N);R(bx-6+off,by-5,3,3,P);R(bx+6+off,by-5,3,3,P);
    R(bx-2+off,by+1,11,4,O);R(bx-7+off,by+8,14,3,N);
  }
  if(act>=1&&fl.ph==='air'){gullS(56+Math.sin(t*2.4)*18,96+Math.cos(t*3)*8,.9,true);gullS(276+Math.cos(t*2.1)*18,98+Math.sin(t*3)*8,.9,true)}
  if(act>=3&&fl.ph==='air'){const r=22+((t*120)%70);cx.strokeStyle=Y;cx.lineWidth=2;cx.beginPath();cx.arc(198,122,r,0,Math.PI*2);cx.stroke()}
}
function drawKrakenAndWhale(py,act){
  if(krakenFly>0){
    const kx=160+krakenFly*55,ky=74-krakenFly*20,ks=Math.max(.14,1-krakenFly*.5);
    if(ks>.2){R(kx-11*ks,ky-11*ks,22*ks,22*ks,PR);R(kx-7*ks,ky-18*ks,14*ks,7*ks,N)}
    else T('✦',kx,ky,Y,14,null,1);
  }else if(fl.ph!=='land'){
    const kx=160+Math.sin(t*2.0)*50,ky=78+Math.sin(t*3.5)*3,col=bossHit>0?(Math.floor(t*30)&1?P:Y):(act>=2?RD:PR);
    for(let k=-2;k<=2;k++)R(kx+k*12-2,ky+9+Math.sin(t*7+k)*5,4,13,col);
    R(kx-15,ky-9,30,19,col);R(kx-11,ky-13,22,6,col);
    const hb=Math.round(hatBounce);
    R(kx-13,ky-15-hb,26,3,N);R(kx-8,ky-25-hb,16,10,N);R(kx-8,ky-17-hb,16,2,Y);
    R(kx-8,ky-3,5,4,Y);R(kx+3,ky-3,5,4,Y);R(kx-6,ky-2,2,2,N);R(kx+5,ky-2,2,2,N);R(kx-9,ky+4,18,2,W);
  }
  shots.forEach(s=>{R(s.x-3,s.y-3,6,6,CY);R(s.x-1,s.y-1,2,2,W)});
  const wy=212+Math.round(Math.sin(t*3)*2),tf=Math.round(Math.sin(t*5)*3);
  if(h>3){
    const top=py-1,bot=wy-14,jh=Math.max(0,bot-top),sw=10+act*2+Math.round(Math.sin(t*15)*2);
    R(160-sw/2,top,sw,jh,act>=2?CY:IC);R(160-sw/2+2,top,sw-4,jh,act>=3?Y:W);
    for(let y=top+4;y<bot;y+=7)R(160-sw/2-2,y+Math.round((t*45)%7),sw+4,2,W);
    R(140,py-2,40,4,W);R(144,py+2,32,3,CY);
  }
  R(124,wy-14,72,18,B2);R(130,wy-18,60,6,B2);R(134,wy-2,52,6,IC);
  R(110,wy-14+tf,16,6,B2);R(104,wy-19+tf,10,5,B2);R(104,wy-8+tf,10,4,B2);R(152,wy-4,14,6,B1);
  if(act>=2){R(174,wy-12,18,5,N);R(176,wy-11,6,2,CY);R(184,wy-11,6,2,CY)}
  else{const bl=(t%3.6)<.14;R(180,wy-11,5,bl?2:5,W);if(!bl)R(182,wy-10,2,3,N)}
  R(184,wy-3,8,2,N);R(156,wy-20,8,3,W);
}
function drawUfoRival(act){
  const left=Math.max(0,fl.need-fl.got);
  if(fl.ph==='land'||(fl.ph==='air'&&left<=5)){
    const fy=fl.ph==='land'?88:Math.round(52+(1-left/5)*44);
    for(let i=0;i<16;i++)R(64+i*12,fy,12,6,i&1?W:N);
    if(fl.ph==='land')T('CHEGADA!',160,fy-4,Y,11,null,1);
  }
  if(fl.ph==='land')return;
  const ux=act===0?236+Math.sin(t*3)*14:act===1?232+Math.sin(t*2)*8:act===2?226+Math.sin(t*6)*3:44;
  const uy=act===0?96:act===1?124+Math.sin(t*4)*5:act===2?148+Math.sin(t*8)*4:166;
  R(ux-16,uy,32,6,G1);R(ux-10,uy-7,20,7,CY);R(ux-6,uy-5,4,4,GN);R(ux+2,uy-5,4,4,GN);R(ux-5,uy-4,2,2,N);R(ux+3,uy-4,2,2,N);
  for(let i=-12;i<=12;i+=8)R(ux+i-1,uy+5,3,2,(Math.floor(t*10)+i)&1?Y:P);
  if(act>=2&&Math.random()<.5)parts.push({x:ux,y:uy-6,vx:-15+(Math.random()-.5)*14,vy:25,l:.6,c:G1,g:0});
}
function sealS(x,y){
  const b=Math.round(Math.abs(Math.sin(t*6))*14);
  R(x-10,y-8,20,8,G1);R(x-4,y-16,10,9,G1);R(x+2,y-14,2,2,N);R(x+5,y-11,3,2,N);R(x-14,y-3,6,3,G1);R(x+8,y-3,6,3,G1);
  R(x-1,y-30-b,8,8,P);R(x+1,y-30-b,4,8,W);R(x-1,y-27-b,8,2,Y);
}
function drawHat(x,y){
  const rp=(a,b,w,h0,c)=>R(x+a*2,y+b*2,w*2,h0*2,c);
  if(curHat==='pirate'){rp(-6,-20,12,2,N);rp(-4,-23,8,3,N);rp(-1,-22,2,2,W)}
  else if(curHat==='shades'){rp(-4,-15,8,2,N);rp(-3,-15,2,1,CY);rp(1,-15,2,1,P)}
  else if(curHat==='tophat'){rp(-5,-20,10,1,N);rp(-3,-25,6,5,N);rp(-3,-21,6,1,Y)}
  else if(curHat==='crown'){rp(-4,-21,8,3,Y);rp(-4,-23,2,2,Y);rp(-1,-23,2,2,Y);rp(2,-23,2,2,Y);rp(-1,-20,2,1,P)}
  else if(curHat==='astro'){cx.strokeStyle=Y;cx.lineWidth=2;cx.strokeRect(x-11,y-37,22,18);R(x-8,y-35,6,2,W)}
}
function pipo(x,y,pose,rocketOn){
  const rp=(a,b,w,h0,c)=>R(x+a*2,y+b*2,w*2,h0*2,c);
  const bl=(t%3.2)<.12,wig=Math.round(Math.sin(t*14)),scw=Math.round(Math.sin(t*12));
  cx.save();cx.translate(x,y-16);
  if(flipA>0)cx.rotate(-flipA);
  else if(st==='run'&&h<2&&Math.abs(curv)>10)cx.rotate(curv*.004);
  cx.scale(sqX,sqY);cx.translate(-x,-(y-16));
  if(feverT>0||(st==='fly'&&fl&&flyAct()>=3))R(x-16,y-36,32,34,'rgba(255,210,63,.22)');
  if(pose==='rocket'){
    rp(-7,-11,3,7,G1);rp(4,-11,3,7,G1);rp(-7,-12,3,2,P);rp(4,-12,3,2,P);
    if(rocketOn){const flh=5+Math.round(Math.abs(Math.sin(t*30))*4);
      rp(-7,-4,3,flh,O);rp(-6,-4,1,flh-1,Y);rp(4,-4,3,flh,O);rp(5,-4,1,flh-1,Y)}
  }
  rp(-7,-2,14,2,B2);rp(-8,-1,2,1,O);rp(-3,-3,2,1,O);rp(1,-3,2,1,O);rp(-4,-11,8,8,N);rp(-2,-9,4,6,W);
  const sc1=feverT>0?pick([Y,AU,CY,P,O]):O;
  rp(-4,-11,8,1,sc1);rp(4,-11+scw,3,1,sc1);rp(6,-10+scw,2,1,Y);
  const up=pose==='cheer'||pose==='fly'||pose==='kite'||pose==='rocket',fy=pose==='bump'?-13:up?-13+wig:-10;
  rp(-6,fy,2,5,N);rp(4,up&&pose!=='kite'?-13-wig:fy,2,5,N);rp(-4,-16,8,6,N);
  if(happyT>0&&(pose==='fly'||pose==='kite'||pose==='rocket'||pose==='stand')){rp(-3,-14,2,1,W);rp(1,-14,2,1,W)}
  else if(bl||pose==='wait'){rp(-3,-13,2,1,W);rp(1,-13,2,1,W)}
  else{rp(-3,-14,2,2,W);rp(1,-14,2,2,W);rp(-2,-13,1,1,N);rp(2,-13,1,1,N)}
  if(pose==='bump'||pose==='fly'||pose==='kite'||pose==='rocket')rp(-1,-11,2,1,P);
  rp(-1,-12,2,1,O);rp(-1,-17,2,1,Y);
  cx.strokeStyle=curHat==='astro'?Y:IC;cx.lineWidth=2;cx.strokeRect(x-11,y-37,22,18);R(x-8,y-35,4,2,W);
  drawHat(x,y);
  if(pose==='wait')T('♪',x+22,y-40+Math.round(Math.sin(t*4)*3),Y,12);
  cx.restore();
}
function iceberg(){
  const o=(1-Math.min(1,restT/1.2))*90,s=stars[leg];
  for(let i=0;i<40;i++){const w=60+i*3.2;R(160-w,112+i+o,w*2,1,i<4?W:(i%8<4?IC:B2))}
  const cy=146+o,eat=restT>1.3&&restT<3.1&&(Math.floor(restT*6)&1),hop=restT>3.1&&s===3?Math.round(Math.abs(Math.sin(t*8))*6):0;
  if(leg===0){
    R(148,cy-12-hop,24,12,'#8d7b94');R(152,cy-22-hop,16,10,'#a692ad');R(150,cy-26-hop,20,5,P);
    R(154,cy-19-hop,4,3,W);R(162,cy-19-hop,4,3,W);R(155,cy-18-hop,2,2,N);R(163,cy-18-hop,2,2,N);
    R(156,cy-14-hop,2,5,W);R(162,cy-14-hop,2,5,W);if(restT>3.1)R(172,cy-10-hop,10,4,O);
  }else if(leg===1){
    const bcol=(Math.floor(t*8)&1)?CY:P;
    R(144,cy-8,32,8,N);R(146,cy-6,10,4,bcol);R(164,cy-6,10,4,AU);
    R(150,cy-22-hop,20,14,W);R(148,cy-26-hop,5,5,W);R(167,cy-26-hop,5,5,W);
    R(147,cy-22-hop,3,7,P);R(170,cy-22-hop,3,7,P);R(150,cy-26-hop,20,2,P);
    R(153,cy-18-hop,14,4,N);R(155,cy-17-hop,4,2,CY);R(161,cy-17-hop,4,2,CY);
  }else{
    R(144,cy-28,32,28,IC);R(146,cy-26,28,24,B2);R(148,cy-12-hop,24,12,RD);
    R(152,cy-14-hop,16,14,N);R(155,cy-12-hop,10,10,W);R(154,cy-23-hop,12,9,N);
    R(154,cy-28-hop,12,5,Y);R(154,cy-31-hop,3,3,Y);R(158,cy-31-hop,4,3,Y);R(163,cy-31-hop,3,3,Y);
    R(156,cy-20-hop,2,2,W);R(162,cy-20-hop,2,2,W);R(158,cy-17-hop,4,eat?4:2,O);
  }
  if(restT>3.1){T('★'.repeat(s),160,cy-35,Y,14);if(tip)T(tip,160,59,Y,10,null,1)}
}
function drawProgress(){
  if(st!=='run'&&(st!=='fly'||gameMode==='force'))return;
  const x0=84,w=120,len=Math.max(1,legEnd-legStart),fr=clamp((p-legStart)/len,0,1);
  R(x0-1,7,w+2,6,N);R(x0,8,w,4,B1);R(x0,8,w*fr,4,feverT>0?Y:IC);
  for(const l of longs){const lx=x0+((l.p-legStart)/len)*w;R(lx-1,6,3,8,l.done?G1:EV[l.kind].col)}
  R(x0+w*fr-1,6,3,8,Y);
}
/* Faixa Única de Comando ("Semáforo de Ação" 12px alto contraste) */
function drawCue(text,col,border){
  R(12,23,296,21,'rgba(7,11,26,.92)');R(12,23,296,2,border||col);R(12,42,296,2,border||col);
  T(text,160,37,col,12,null,1);
}

function draw(){
  const mode=(st==='lost'||st==='resume'||st==='pause')?prev:st;
  cx.save();
  if(bumpT>1.0||shk>0)cx.translate(Math.round((Math.random()-.5)*4),Math.round((Math.random()-.5)*4));
  drawSky(mode);ground(mode);
  if(cam){R(cam.x-12,cam.y,24,4,G1);R(cam.x-6,cam.y-4,12,4,CY);R(cam.x-2,cam.y+4,4,2,Y)}
  if(seal)sealS(262,178);
  if(mode==='rest')iceberg();

  /* peixes do passo 2 do treino */
  if(mode==='train'&&train&&train.step===1&&train.doneT<=0){
    train.fishes.forEach(q=>{const s=60/(60+Math.max(0,q.d)),y=hzNow+(GY-hzNow)*s;fishS(160,y,lvl(s)*1.1,Y)});
  }

  let nearH=999,nearA=999,nearR=999,nearL=null;
  if(mode==='run'){
    objs.filter(o=>o.p>=p&&o.p-p<260&&o.k!=='canal').sort((a,b)=>b.p-a.p).forEach(o=>{
      const d=o.p-p,s=60/(60+d),y=hzNow+(GY-hzNow)*s,xc=xOf(s),q=lvl(s);
      if(o.k==='fish')fishS(xc,y,q,feverT>0?AU:Y);
      else if(o.k==='airf'){fishS(xc,y-32*q,q,CY);R(xc-3*q,y-37*q,2*q,2*q,W);nearA=Math.min(nearA,d)}
      else if(o.k==='gold'){fishS(xc,y-35*q,q*1.6,Y);if(Math.sin(t*10)>0)R(xc-10*q,y-52*q,3*q,3*q,W);nearA=Math.min(nearA,d)}
      else if(o.k==='puf'){puff(xc,y,q);nearH=Math.min(nearH,d)}
      else if(o.k==='wf')fishS(xc,y-34*q,q,o.rail?AU:Y);
      else if(o.k==='gate'){gateS(xc,y,q,s);nearH=Math.min(nearH,d)}
      else if(o.k==='ramp'){rampS(xc,y,q);nearR=Math.min(nearR,d)}
      else if(o.k==='walrus'){walrusS(xc,y,q,false);nearA=Math.min(nearA,d)}
      else if(o.k==='long'){
        if(o.kind==='kite'){const ky=y-86*q+Math.sin(t*2)*3*q;cx.strokeStyle=W;cx.lineWidth=1;cx.beginPath();cx.moveTo(xc,y);cx.lineTo(xc,ky+16*q*1.4);cx.stroke();kiteS(xc,ky,q*1.4,false)}
        else if(o.kind==='whale')whaleIcon(xc,y,q*1.3);
        else rocketIcon(xc,y,q*1.3);
        if(!nearL||d<nearL.d)nearL={d,kind:o.kind};
      }else{R(xc-9*q,y-2*q,18*q,2*q,B1);gullS(xc-3*q,y-40*q,q,true);nearA=Math.min(nearA,d)}
    });
  }

  const px=pipoX(),py=Math.round(200-h+Math.sin(t*10)*((mode==='run'||mode==='train'||mode==='forceRest')&&h<1?1:0));
  if(walPop)walrusS(walPop.x,walPop.y,1,true);
  if(mode==='fly'&&fl){
    const act=flyAct(),fr=clamp(fl.got/fl.need,0,1);
    if(fl.kind==='kite')drawAvalanche(act,fr);
    else if(fl.kind==='rocket')drawUfoRival(act);
    sf.slice().sort((a,b)=>b.d-a.d).forEach(q=>{
      const s=60/(60+q.d),y=hzNow+(GY-hzNow)*s-(fl.kind==='whale'?52:70)*s,xc=fl.kind==='kite'?160+(px-160)*s:xOf(s),sz=lvl(s)*(q.g?1.6:1.1);
      if(fl.kind==='rocket')R(xc+4*sz,y-4*sz,8*sz,2*sz,q.g?Y:CY);
      fishS(xc,y,sz,Y);if(q.g&&Math.sin(t*10)>0)R(xc-6,y-14*lvl(s),3,3,W);
    });
    if(fl.kind==='kite'){
      const kx=262+Math.sin(t*1.5)*7,ky=fl.ph==='land'?py-64-fl.lt*50:py-64+Math.sin(t*2.4)*3;
      cx.strokeStyle=W;cx.lineWidth=1;cx.beginPath();cx.moveTo(px+8,py-26);cx.lineTo(kx,ky+16);cx.stroke();kiteS(kx,ky,1,act>=2);
    }else if(fl.kind==='whale')drawKrakenAndWhale(py,act);
  }
  ghosts.forEach(g=>{cx.save();cx.globalAlpha=g.l*1.5;cx.translate(g.x,g.y-16);if(g.a)cx.rotate(-g.a);R(-9,-18,18,30,g.c);cx.restore()});
  const a=isAir(),wet=mode==='run'&&swim;
  const pose=st==='lost'?'wait':mode==='rest'?(restT>3.1&&stars[leg]<2?'bump':'cheer'):mode==='end'?'cheer':
    mode==='fly'&&fl?(fl.kind==='rocket'&&fl.ph!=='wait'?'rocket':fl.ph==='air'?(fl.up?(fl.kind==='kite'?'kite':'fly'):'fly'):fl.ph==='land'?'cheer':'stand'):
    (mode==='run'||mode==='train')?(h>3?'fly':bumpT>0?'bump':'stand'):'stand';
  if(h>2&&!(mode==='fly'&&fl&&fl.kind==='whale'))R(px-12+h/6,205,24-h/4,3,B1);
  if(wet){cx.save();cx.beginPath();cx.rect(0,0,320,204);cx.clip();pipo(px,218+Math.round(Math.sin(t*5)),pose,false);cx.restore();R(px-20,203,40,2,IC);R(px-14+Math.round(Math.sin(t*4)*3),206,28,1,W)}
  else pipo(px,py,pose,mode==='fly'&&fl&&fl.kind==='rocket'&&fl.ph==='air'&&fl.up);
  if(flyer)gullS(flyer.x,flyer.y,1.4,flyer.f);
  snow.forEach(q=>R(q.x,q.y,q.sz,q.sz,'rgba(240,248,255,.5)'));
  parts.forEach(q=>R(q.x,q.y,2,2,q.c));
  pops.forEach(q=>T(q.s,q.x,q.y,q.c,10,null,1));
  cx.restore();

  /* ===== HUD & SEMÁFORO ÚNICO (fontes ≥ 10px, zero poluição) ===== */
  const blink=Math.sin(t*10)>0,C=cfg();

  /* 1. Barra superior (não aparece em Menu nem Tela Final!) */
  if(st!=='menu'&&st!=='end'){
    R(0,0,320,21,'rgba(7,11,26,.82)');
    fishS(13,16,.85,Y);T('×'+fish,23,16,Y,11,'left');
    drawProgress();
    if(st==='train')T('TREINO '+(train?train.step+1:1)+'/3',314,15,AU,10,'right');
    else if(gameMode==='force')T('DESAFIO '+(forceIdx+1)+'/3',314,15,CY,10,'right');
    else T('FASE '+(Math.min(3,leg+1))+'/3 ★'+stars.reduce((a,b)=>a+b,0),314,15,W,10,'right');
    /* pílula nítida do estado da perna no canto inferior esquerdo (10px) */
    R(4,205,conf?106:78,16,'rgba(7,11,26,.85)');
    R(7,210,6,6,sigOK?(conf?CY:AU):P);
    T(conf?'▲ NO ALTO':'▼ NO CHÃO',17,216,conf?CY:AU,10,'left');
  }

  /* 2. Treino Guiado de 3 Passos */
  if(st==='train'&&train){
    if(train.doneT>0){
      const msgs=['MUITO BEM! PIPO VOOU!','ISSO! NO CHÃO VOCÊ DESCANSA!','PERFEITO! VAMOS JOGAR!'];
      drawCue(msgs[train.step],AU,AU);
    }else if(train.step===0){
      drawCue('▲ PASSO 1: LEVANTE A PERNA!',blink?Y:O,O);
      R(36,48,248,18,'rgba(7,11,26,.82)');T('Pipo sobe quando sua perna levanta',160,60,W,10);
    }else if(train.step===1){
      drawCue('▼ PASSO 2: ABAIXE A PERNA!',AU,AU);
      R(30,48,260,18,'rgba(7,11,26,.82)');T('No chão você descansa e pega peixes',160,60,W,10);
    }else{
      const left=Math.max(1,Math.ceil(3-train.prog));
      drawCue('▲ PASSO 3: SEGURE! FALTAM '+left+' s',CY,CY);
      R(59,49,202,12,N);R(60,50,200,10,B1);R(60,50,200*clamp(train.prog/3,0,1),10,AU);
    }
  }

  /* 3. Descanso Guiado no Modo Desafio de Força */
  if(st==='forceRest'){
    const left=Math.max(1,Math.ceil(forceRestT));
    drawCue('▼ DESCANSE A PERNA · '+left+' s',AU,AU);
    R(59,49,202,10,N);R(60,50,200,8,B1);R(60,50,200*clamp(1-forceRestT/12,0,1),8,AU);
    R(20,64,280,18,'rgba(7,11,26,.85)');T('Ótima série! Respire e relaxe a perna.',160,76,W,10);
    if(forceRestT<9){R(28,86,264,16,'rgba(7,11,26,.82)');T('Toque ou Enter para pular descanso',160,97,Y,10)}
  }

  /* 4. Semáforo Único durante a corrida (st==='run') */
  if(st==='run'){
    if(inC){
      const left=Math.max(0,(inC.p+inC.len-p)/Math.max(1,spd));
      if(swim)drawCue('▲ LEVANTE A PERNA! '+dec(left)+' s',P,P);
      else drawCue('▲ SEGURE NO ALTO! '+dec(left)+' s',inC.rail?CY:AU,inC.rail?CY:AU);
    }else if(nearH<C.urgH&&!a){
      drawCue('▲ LEVANTE A PERNA AGORA!',blink?Y:O,P);
    }else if(nearH<C.nearH){
      drawCue(a?'✓ MUITO BEM! MANTENHA!':'▲ PREPARE PARA LEVANTAR!',a?AU:Y,a?AU:O);
    }else if(nearR<C.nearR){
      drawCue(a?'✓ SALTO PRONTO!':'▲ RAMPA! LEVANTE A PERNA!',a?AU:Y,Y);
    }else if(nearA<C.nearA){
      drawCue(a?'✓ PEGUE NO ALTO!':'▲ BÔNUS NO ALTO! LEVANTE!',a?AU:Y,Y);
    }else{
      const c=cans.find(c=>c.p>p&&c.p-p<240);
      if(c)drawCue('▲ '+(c.rail?'TRILHO':'CANAL')+'! SEGURE ~'+Math.round(c.len/C.canal)+' s',CY,CY);
      else if(nearL&&nearL.d<240)drawCue('▲ '+EV[nearL.kind].cue,EV[nearL.kind].col,EV[nearL.kind].col);
      else if(feverT>0)drawCue('★ FESTA DA AURORA · PEIXES ×2 ★',blink?Y:AU,Y);
      else if(banner)drawCue(banner.text,Y,CY);
      else if(idleUp>1.8)drawCue('▼ PODE ABAIXAR E DESCANSAR!',AU,AU);
      else drawCue('▼ NO CHÃO: DESCANSE E PEGUE PEIXES',AU,B2);
    }
  }

  /* 5. Semáforo Único + Barra + Contador SEMPRE visível nos eventos >15 s (st==='fly') */
  if(st==='fly'&&fl){
    const m=EV[fl.kind];
    if(fl.ph==='wait'){
      drawCue('▲ '+m.wait,blink?Y:O,P);
      R(58,48,204,18,'rgba(7,11,26,.82)');T('Segure por '+fl.need+' s · Sem pressa!',160,60,W,10);
    }else if(fl.ph==='air'){
      const left=Math.max(0,Math.ceil(fl.need-fl.got)),fr=clamp(fl.got/fl.need,0,1);
      if(fl.up)drawCue('▲ SEGURE NO ALTO! FALTAM '+left+' s',left<=5?(blink?Y:O):m.col,m.col);
      else drawCue('▲ LEVANTE PARA CONTINUAR!',blink?Y:P,P);
      /* barra de progresso grande e nítida logo abaixo da faixa */
      R(49,47,222,10,N);R(50,48,220,8,B1);R(50,48,220*fr,8,fl.up?m.col:G1);
      for(let k=1;k<=3;k++)R(50+k*55,47,1,10,fr>=k*.25?Y:W);
      if(fl.up&&left<=5)T(left+'!',160,82,blink?Y:O,22,null,1);
      if(!fl.up){R(40,60,240,16,'rgba(7,11,26,.82)');T('Descanse se precisar · Sem pressa',160,71,W,10)}
    }else if(fl.ph==='land'){
      drawCue('▼ PODE ABAIXAR E DESCANSAR!',AU,AU);
    }
    if(fl.msg&&fl.msgT>0){
      const ly=fl.kind==='whale'?172:186;
      R(16,ly,288,18,'rgba(7,11,26,.9)');R(16,ly,288,1,m.col);T(fl.msg,160,ly+13,W,10);
    }
  }

  /* 6. Descanso no Iceberg (st==='rest') */
  if(st==='rest'){
    const left=Math.max(1,Math.ceil(9-restT));
    drawCue('▼ DESCANSE UM POUCO · '+left+' s',AU,AU);
    bubs.forEach(b=>{
      cx.font='bold 10px monospace';const w=cx.measureText(b.s).width+14,x=clamp(b.x-w/2,4,316-w);
      R(x-1,b.y-1,w+2,19,N);R(x,b.y,w,17,W);R(b.x-2,b.y+17,4,3,W);cx.fillStyle=N;cx.textAlign='center';cx.fillText(b.s,x+w/2,b.y+12);
    });
  }

  /* 7. Perda de sinal e contagem de retomada */
  if(st==='lost'){R(0,72,320,44,'rgba(7,11,26,.92)');T('SINAL PERDIDO · SEM PRESSA!',160,92,P,12);T('O jogo volta sozinho quando o sinal retornar',160,108,W,10)}
  if(st==='resume'){R(60,74,200,34,'rgba(7,11,26,.9)');T('VOLTANDO EM '+Math.ceil(resT)+'...',160,96,Y,14,null,1)}

  /* 8. Tela Final limpa e legível (Medalhas OURO/PRATA/BRONZE + 4 métricas grandes) */
  if(st==='end'){
    const tot=stars.reduce((a,b)=>a+b,0),ok=M.holds.filter(x=>x.ok).length,rk=getRank();
    const bestRun=Math.max(M.longest,M.holds.reduce((a,x)=>Math.max(a,x.best),0));
    R(8,10,304,158,'rgba(7,11,26,.94)');R(8,10,304,2,rk.c);R(8,166,304,2,rk.c);
    T('PARABÉNS!',116,34,Y,16);
    if(stamped){
      const sc0=1+Math.max(0,1-(endT-.85)*6)*1.2;
      cx.save();cx.translate(256,34);cx.scale(sc0,sc0);
      R(-48,-16,96,32,N);R(-46,-14,92,28,rk.c);T(rk.r,0,5,N,14);cx.restore();
    }
    T(rk.title,160,58,CY,10);
    if(gameMode==='force'){
      T('PONTOS: '+endDisp,160,78,W,11);
      T('DESAFIOS VENCIDOS: '+ok+' DE '+M.holds.length,160,96,AU,11);
    }else{
      T('PONTOS: '+endDisp+' · ESTRELAS: '+tot+'/9 ★',160,78,W,11);
      T('DESAFIOS VENCIDOS: '+ok+' DE '+M.holds.length,160,96,AU,11);
    }
    T('MAIOR TEMPO NO ALTO: '+dec(bestRun)+' s',160,114,Y,11);
    T('TEMPO DE EXERCÍCIO: '+mmss(M.up),160,132,IC,11);
    const nextLocked=HATS.find(x=>!unlocked.has(x.id));
    T(newHatMsg||(nextLocked?'PRÓX. CHAPÉU: '+nextLocked.name:'TODOS OS CHAPÉUS LIBERADOS!'),160,152,Y,10);
  }
}

/* ===== Overlays HTML (Menu, Pausa, Fim, Pular Treino) + Controles ===== */
const scr=document.getElementById('scr'),snb=document.getElementById('snb'),hatb=document.getElementById('hatb'),fsb=document.getElementById('fsb'),menuBtn=document.getElementById('menuBtn');
const menuOv=document.getElementById('menuOv'),pauseOv=document.getElementById('pauseOv'),endActs=document.getElementById('endActs'),skipTrain=document.getElementById('skipTrain');
const mCards=[...document.querySelectorAll('.mcard')],mRec=document.getElementById('mRec'),mWarn=document.getElementById('mWarn');
const bTrain=document.getElementById('bTrain'),bCalm=document.getElementById('bCalm');
const fsMenuEl=document.getElementById('fsMenu'),legBtnEl=document.getElementById('leg'),fsLegEl=document.getElementById('fsLeg');

function updateMenuSelection(){
  mCards.forEach((c,i)=>c.classList.toggle('sel',i===menuIdx));
  if(bTrain)bTrain.style.display=trained?'none':'inline-block';
  if(bCalm)bCalm.style.display=trained?'inline-block':'none';
  if(mRec)mRec.textContent='Recorde: '+bestScore+' pts · '+best+'/9 ★';
  if(mWarn)mWarn.classList.toggle('show',!sigOK);
}
function syncOverlays(){
  if(menuOv)menuOv.classList.toggle('show',st==='menu');
  if(pauseOv)pauseOv.classList.toggle('show',st==='pause');
  if(endActs)endActs.classList.toggle('show',st==='end');
  if(skipTrain)skipTrain.classList.toggle('show',st==='train');
  if(fsMenuEl)fsMenuEl.style.display=st==='menu'?'none':'inline-block';
  if(menuBtn)menuBtn.textContent=st==='menu'?'▶ COMEÇAR':st==='pause'?'▶ CONTINUAR':'⏸ PAUSA / MENU';
  if(st==='menu'){menuIdx=trained?1:0;updateMenuSelection()}
  syncBgmPlay();
}
mCards.forEach((c,i)=>{
  c.addEventListener('click',()=>{menuIdx=i;startMode(c.dataset.mode)});
});
document.getElementById('pResume').onclick=()=>togglePause();
document.getElementById('pRestart').onclick=()=>startMode(prev==='train'?'train':gameMode);
document.getElementById('pMenu').onclick=()=>goMenu();
document.getElementById('eAgain').onclick=()=>startMode(gameMode);
document.getElementById('eMenu').onclick=()=>goMenu();
skipTrain.onclick=()=>{trained=true;try{localStorage.setItem('pipoTrained','1')}catch(e){}startMode('calm')};

/* áudio UI */
const volBgmEl=document.getElementById('volBgm'),volSfxEl=document.getElementById('volSfx'),fsVolEl=document.getElementById('fsVol');
const volBgmTxt=document.getElementById('volBgmTxt'),volSfxTxt=document.getElementById('volSfxTxt'),fsMuteEl=document.getElementById('fsMute'),astat=document.getElementById('astat');
function applyAudioUI(){
  const bp=Math.round(bgmVol*100),sp=Math.round(sfxVol*100);
  if(volBgmEl)volBgmEl.value=String(bp);
  if(fsVolEl)fsVolEl.value=String(bp);
  if(volSfxEl)volSfxEl.value=String(sp);
  if(volBgmTxt)volBgmTxt.textContent=bp+'%';
  if(volSfxTxt)volSfxTxt.textContent=sp+'%';
  if(snb)snb.textContent=mute?'🔇 SEM SOM':'🔊 SOM LIGADO';
  if(fsMuteEl)fsMuteEl.textContent=mute?'🔇':'🔊';
  if(sfxG&&ac)sfxG.gain.setTargetAtTime(mute?0:sfxVol,ac.currentTime,.03);
  if(bgm)try{bgm.volume=mute?0:bgmVol}catch(e){}
  syncBgmPlay();
}
function setBgmVol(v){
  unlock();bgmVol=clamp(v,0,1);curBgmVol=bgmVol;if(bgmVol>0&&mute)mute=false;
  try{localStorage.setItem('pipoVolBgm',bgmVol.toFixed(2));localStorage.setItem('pipoMute',mute?'1':'0')}catch(e){}
  applyAudioUI();
}
function setSfxVol(v){
  unlock();sfxVol=clamp(v,0,1);if(sfxVol>0&&mute)mute=false;
  try{localStorage.setItem('pipoVolSfx',sfxVol.toFixed(2));localStorage.setItem('pipoMute',mute?'1':'0')}catch(e){}
  applyAudioUI();
}
function toggleSnd(){unlock();mute=!mute;try{localStorage.setItem('pipoMute',mute?'1':'0')}catch(e){}applyAudioUI()}
if(volBgmEl){volBgmEl.addEventListener('input',()=>setBgmVol(+volBgmEl.value/100));volBgmEl.addEventListener('change',()=>volBgmEl.blur())}
if(fsVolEl){fsVolEl.addEventListener('input',()=>setBgmVol(+fsVolEl.value/100));fsVolEl.addEventListener('change',()=>fsVolEl.blur())}
if(volSfxEl){volSfxEl.addEventListener('input',()=>setSfxVol(+volSfxEl.value/100));volSfxEl.addEventListener('change',()=>{snd(660,880,.08,'triangle',.05);volSfxEl.blur()})}
if(bgm&&astat){
  const okBgm=()=>{astat.textContent='🎵 Música pronta ✓';astat.style.color='#5cf2a8'};
  bgm.addEventListener('canplay',okBgm);
  bgm.addEventListener('loadeddata',okBgm);
  if(bgm.readyState>=2)okBgm();
  bgm.addEventListener('error',()=>{astat.textContent='⚠ Música /audio.ogg não encontrada';astat.style.color='#f25c78'});
}

/* tela cheia */
let fsIdle=null;
function isFS(){return !!(document.fullscreenElement||document.webkitFullscreenElement||scr.classList.contains('fs-fallback'))}
function updateFSUI(){
  const on=isFS();if(fsb)fsb.textContent=on?'⛶ SAIR TELA CHEIA':'⛶ TELA CHEIA';
  if(!on){scr.classList.remove('fs-idle');if(fsIdle)clearTimeout(fsIdle)}else pokeFS();
}
function pokeFS(){if(!isFS())return;scr.classList.remove('fs-idle');if(fsIdle)clearTimeout(fsIdle);fsIdle=setTimeout(()=>{if(isFS())scr.classList.add('fs-idle')},2800)}
function toggleFS(){
  unlock();
  if(document.fullscreenElement||document.webkitFullscreenElement){
    const ex=document.exitFullscreen||document.webkitExitFullscreen;if(ex)try{ex.call(document)}catch(e){}
    scr.classList.remove('fs-fallback');updateFSUI();return;
  }
  if(scr.classList.contains('fs-fallback')){scr.classList.remove('fs-fallback');updateFSUI();return}
  const req=scr.requestFullscreen||scr.webkitRequestFullscreen;
  if(req){try{const pr=req.call(scr);if(pr&&pr.catch)pr.catch(()=>{scr.classList.add('fs-fallback');updateFSUI()})}catch(e){scr.classList.add('fs-fallback');updateFSUI()}}
  else{scr.classList.add('fs-fallback');updateFSUI()}
}
document.addEventListener('fullscreenchange',updateFSUI);
document.addEventListener('webkitfullscreenchange',updateFSUI);
scr.addEventListener('pointermove',pokeFS);scr.addEventListener('pointerdown',pokeFS);
document.getElementById('fsExit').onclick=e=>{e.stopPropagation();toggleFS()};
if(fsMenuEl)fsMenuEl.onclick=e=>{e.stopPropagation();togglePause()};
if(fsMuteEl)fsMuteEl.onclick=e=>{e.stopPropagation();toggleSnd()};
if(fsb)fsb.onclick=toggleFS;

/* laço e entradas */
const browserPerf={frames:0,fps:0,frameMaxMs:0,windowStart:performance.now(),windowFrames:0};
let last=performance.now();
function loop(n){
  const rawDt=Math.max(0,(n-last)/1000);browserPerf.frames++;browserPerf.windowFrames++;
  browserPerf.frameMaxMs=Math.max(browserPerf.frameMaxMs,rawDt*1000);
  if(n-browserPerf.windowStart>=1000){browserPerf.fps=Math.round(browserPerf.windowFrames*1000/(n-browserPerf.windowStart));browserPerf.windowFrames=0;browserPerf.windowStart=n;browserPerf.frameMaxMs=0}
  const dt=Math.min(.05,rawDt);last=n;update(dt);draw();requestAnimationFrame(loop)
}
requestAnimationFrame(loop);

function togglePause(){
  if(st==='menu'){startMode(mCards[menuIdx]?mCards[menuIdx].dataset.mode:'calm');return}
  if(st==='run'||st==='rest'||st==='fly'||st==='train'||st==='forceRest'){prev=st;st='pause';syncOverlays()}
  else if(st==='resume'){st='pause';syncOverlays()}
  else if(st==='pause'){if(sigOK){st='resume';resT=1.5}else st='lost';syncOverlays()}
}
function onTapCanvas(){
  unlock();
  if(st==='forceRest'&&forceRestT<9){forceRestT=.05}
}
cv.addEventListener('pointerdown',onTapCanvas);
if(menuBtn)menuBtn.onclick=togglePause;
addEventListener('keydown',e=>{
  unlock();if(document.activeElement&&document.activeElement.blur)document.activeElement.blur();
  if(e.code==='Space'){e.preventDefault();legKey=true;setLeg()}
  else if(e.code==='KeyI')invKey=true;
  else if(e.repeat)return;
  else if(st==='menu'){
    if(e.code==='Digit1'||e.code==='Numpad1')startMode('train');
    else if(e.code==='Digit2'||e.code==='Numpad2')startMode('calm');
    else if(e.code==='Digit3'||e.code==='Numpad3')startMode('normal');
    else if(e.code==='Digit4'||e.code==='Numpad4')startMode('force');
    else if(e.code==='ArrowRight'){menuIdx=(menuIdx+1)%4;updateMenuSelection()}
    else if(e.code==='ArrowLeft'){menuIdx=(menuIdx+3)%4;updateMenuSelection()}
    else if(e.code==='ArrowDown'||e.code==='ArrowUp'){menuIdx=(menuIdx+2)%4;updateMenuSelection()}
    else if(e.code==='Enter')startMode(mCards[menuIdx].dataset.mode);
    else if(e.code==='KeyF')toggleFS();
    else if(e.code==='KeyC')nextHat();
    else if(e.code==='KeyM')toggleSnd();
  }else{
    if(e.code==='Enter'){
      if(st==='end')startMode(gameMode);
      else if(st==='pause')togglePause();
      else if(st==='forceRest'&&forceRestT<9)forceRestT=.05;
    }else if(e.code==='KeyP')togglePause();
    else if(e.code==='KeyF')toggleFS();
    else if(e.code==='Escape'){
      if(scr.classList.contains('fs-fallback'))toggleFS();
      else if(st==='train'){trained=true;try{localStorage.setItem('pipoTrained','1')}catch(e){}startMode('calm')}
      else if(st==='pause')togglePause();
    }else if(e.code==='KeyC')nextHat();
    else if(e.code==='KeyM')toggleSnd();
  }
});
addEventListener('keyup',e=>{
  if(e.code==='Space'){e.preventDefault();legKey=false;setLeg()}
  else if(e.code==='KeyI')invKey=false;
});
addEventListener('blur',()=>{legKey=legBtn=invKey=invBtn=false;setLeg()});
function hold(id,on,off){
  const b=document.getElementById(id);if(!b)return;b.addEventListener('contextmenu',e=>e.preventDefault());
  b.addEventListener('pointerdown',e=>{e.preventDefault();e.stopPropagation();unlock();b.classList.add('hold');on()});
  ['pointerup','pointerleave','pointercancel'].forEach(ev=>b.addEventListener(ev,()=>{b.classList.remove('hold');off()}));
}
hold('leg',()=>{legBtn=true;setLeg()},()=>{legBtn=false;setLeg()});
hold('fsLeg',()=>{legBtn=true;setLeg()},()=>{legBtn=false;setLeg()});
hold('inv',()=>{invBtn=true},()=>{invBtn=false});
const hs=document.getElementById('holdSel');
if([...hs.options].some(o=>+o.value===holdBase))hs.value=String(holdBase);else holdBase=+hs.value;
hs.addEventListener('change',()=>{holdBase=+hs.value;try{localStorage.setItem('pipoHold',holdBase)}catch(e){}hs.blur()});
snb.onclick=toggleSnd;hatb.onclick=nextHat;
updateHatBtn();applyAudioUI();updateFSUI();syncOverlays();

const led=document.getElementById('led'),ledTxt=document.getElementById('ledTxt');
setInterval(()=>{
  led.className='led'+(sigOK?(conf?' up':''):' lost');
  ledTxt.textContent=sigOK?(conf?'PERNA NO ALTO · '+dec(M.cur)+' s':'SENSOR PRONTO'):'SEM SINAL';
  if(mWarn)mWarn.classList.toggle('show',!sigOK);
  /* feedback vivo do sensor no botão gigante! */
  const upTxt='✓ PERNA NO ALTO! ('+dec(M.cur)+' s)',dnTxt='▲ SEGURE = LEVANTAR PERNA';
  if(legBtnEl){legBtnEl.classList.toggle('up',!!conf);legBtnEl.textContent=conf?upTxt:dnTxt}
  if(fsLegEl){fsLegEl.classList.toggle('up',!!conf);fsLegEl.textContent=conf?upTxt:dnTxt}
  const ok=M.holds.filter(x=>x.ok).length,bh=M.holds.reduce((a,x)=>Math.max(a,x.best),0);
  const evInfo=fl&&fl.ph==='air'?' · '+EV[fl.kind].name+': '+dec(fl.got)+'/'+fl.need+' s':'';
  document.getElementById('sensor').textContent='HC-SR04 '+(extSensor?'ESP32':'simulado')+': '+(dist?dist+' mm':'inválido (0)')+' · estado: '+(conf?'LEVANTADA':'abaixada')+' · sinal: '+(sigOK?'ok':'PERDIDO')+' · modo: '+gameMode+evInfo;
  document.getElementById('m').textContent=
    'navegador: '+browserPerf.fps+' FPS · maior intervalo de quadro: '+dec(browserPerf.frameMaxMs)+' ms · quadros: '+browserPerf.frames+'\n'+
    'amostras válidas: '+(M.tot?Math.round(M.val/M.tot*100):100)+'%   episódios inválidos: '+M.eps+'   transições: '+M.trans+'   latência: '+(M.lat?M.lat+' ms':'-')+'\n'+
    'desafios longos completos: '+ok+'/'+M.holds.length+'   melhor sustentação contínua: '+dec(bh)+' s   quedas nos desafios: '+M.holds.reduce((a,x)=>a+x.drops,0)+'\n'+
    'perna no alto (total): '+mmss(M.up)+'   maior tempo seguido: '+dec(M.longest)+' s   canais/trilhos secos: '+M.cOk+'/'+M.cTot+'\n'+
    'portões/baiacus: '+M.hOk+'/'+M.hTot+'   saltos em rampa: '+M.flips+'   sequência máx: '+M.maxCombo+'   levantadas sem motivo: '+M.free;
},200);
document.getElementById('exportMetrics').addEventListener('click',()=>{
  const dados={projeto:'Pipo: Entrega Gelada',origemSensor:extSensor?'ESP32 (window.pipoSensor)':'simulador local',estadoSensor:sigOK?'valido':'invalido',modo:gameMode,estadoJogo:st,pontuacao:score,melhorPontuacao:bestScore,metricasSensorJogo:{...M,holds:M.holds.map(x=>({...x}))},metricasNavegador:{...browserPerf},exportadoEm:new Date().toISOString(),nota:'Métricas de software e interação; não são avaliação clínica nem medição de força, ângulo ou gasto calórico.'};
  const url=URL.createObjectURL(new Blob([JSON.stringify(dados,null,2)],{type:'application/json'})),a=document.createElement('a');a.href=url;a.download='pipo-metricas-'+new Date().toISOString().replace(/[:.]/g,'-')+'.json';a.click();setTimeout(()=>URL.revokeObjectURL(url),1000);
});
</script>
</body>
</html>
)NEOPIPO";
