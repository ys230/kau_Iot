#include "Task07-C.h"

String html1 = R"rawliteral(<!DOCTYPE html><html>
<head>
    <meta charset='UTF-8' name='viewport\' content='width=device-width, initial-scale=1'>
<link rel='icon\' href='data:,''>
    <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
        .button { background-color: #4CAF50;border: none; color: white; padding: 8px 20px;
            text-decoration: none; font-size: 15px; margin: 2px; cursor: pointer;}
        .button2 {background-color: #555555;}
        table {
            margin: auto;
            text-align: center;
        }
    </style>
</head>

<body>
    <h1>ESP32 Web Server</h1>
    )rawliteral";

String html2 = R"rawliteral(<form name='setAlarmForm' method='post'>
    <table>
        <tr><td>set time</td> 
            <td>
                <select name='Hour' id='Hour'> 
                    <option value="00">0</option> 
                    <option value="01">1</option> 
                    <option value="02">2</option> 
                    <option value="03">3</option> 
                    <option value="04">4</option> 
                    <option value="05">5</option> 
                    <option value="06">6</option> 
                    <option value="07">7</option> 
                    <option value="08">8</option> 
                    <option value="09">9</option> 
                    <option value="10">10</option> 
                    <option value="11">11</option> 
                    <option value="12">12</option> 
                    <option value="13">13</option> 
                    <option value="14">14</option> 
                    <option value="15">15</option> 
                    <option value="16">16</option> 
                    <option value="17">17</option> 
                    <option value="18">18</option> 
                    <option value="19">19</option> 
                    <option value="20">20</option> 
                    <option value="21">21</option> 
                    <option value="22">22</option> 
                    <option value="23">23</option> 
                </select> 
                h
                <select name='Minute' id='Minute'> 
                    <option value="00">0</option> 
                    <option value="01">1</option> 
                    <option value="02">2</option> 
                    <option value="03">3</option> 
                    <option value="04">4</option> 
                    <option value="05">5</option> 
                    <option value="06">6</option> 
                    <option value="07">7</option> 
                    <option value="08">8</option> 
                    <option value="09">9</option> 
                    <option value="10">10</option> 
                    <option value="11">11</option> 
                    <option value="12">12</option> 
                    <option value="13">13</option> 
                    <option value="14">14</option> 
                    <option value="15">15</option> 
                    <option value="16">16</option> 
                    <option value="17">17</option> 
                    <option value="18">18</option> 
                    <option value="19">19</option> 
                    <option value="20">20</option> 
                    <option value="21">21</option> 
                    <option value="22">22</option> 
                    <option value="23">23</option> 
                    <option value="24">24</option> 
                    <option value="25">25</option> 
                    <option value="26">26</option> 
                    <option value="27">27</option> 
                    <option value="28">28</option> 
                    <option value="29">29</option> 
                    <option value="30">30</option> 
                    <option value="31">31</option> 
                    <option value="32">32</option> 
                    <option value="33">33</option> 
                    <option value="34">34</option> 
                    <option value="35">35</option> 
                    <option value="36">36</option> 
                    <option value="37">37</option> 
                    <option value="38">38</option> 
                    <option value="39">39</option> 
                    <option value="40">40</option> 
                    <option value="41">41</option> 
                    <option value="42">42</option> 
                    <option value="43">43</option> 
                    <option value="44">44</option> 
                    <option value="45">45</option> 
                    <option value="46">46</option> 
                    <option value="47">47</option> 
                    <option value="48">48</option> 
                    <option value="49">49</option> 
                    <option value="50">50</option> 
                    <option value="51">51</option> 
                    <option value="52">52</option> 
                    <option value="53">53</option> 
                    <option value="54">54</option> 
                    <option value="55">55</option> 
                    <option value="56">56</option> 
                    <option value="57">57</option> 
                    <option value="58">58</option> 
                    <option value="59">59</option> 
                </select> 
                m
            </td>
            <td>
            
            </td>
            <script>
                let btn = document.createElement("button");
                btn.innerHTML = "Set";
                btn.class = "button";
                btn.onclick = function() {
                    location.href = "/set/h" + document.getElementById("Hour").value + "/m" + document.getElementById("Minute").value;
                };
                document.body.appendChild(btn);
            </script>
        </tr> 
</table></form></body></html>)rawliteral";

void printPage(WiFiClient* client) {
    struct tm timeVal;
    getLocalTime(&timeVal);
    
    client->println(html1);
    client->println("<script>var totalTime=" + String(timeVal.tm_hour*3600+timeVal.tm_min*60+timeVal.tm_sec) + 
          "; setInterval(function(){totalTime++; document.getElementById('timer').innerHTML='NowTime: '+Math.floor(totalTime/3600) + ':' + Math.floor(totalTime%3600/60) + ':' + totalTime%3600%60;}, 1000);</script>");
    client->println(&timeVal, "<h2 id='timer'>NowTime: %H:%M:%S</h2>");
    client->println("Year: "+String(timeVal.tm_year+1900)+", Month: " + String(timeVal.tm_mon+1));
    client->println(html2);
}
