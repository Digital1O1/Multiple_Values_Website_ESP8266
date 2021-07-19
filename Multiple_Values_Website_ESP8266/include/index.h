const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <style>
    .displayobject
    {
       font-family: sans-serif;
       margin: auto;
       text-align: center;
       width: 50%;
       border: 3px solid #000000;
       padding: 10px;
       background: #558ED5;
    }
    h1 {
      font-size: 36px;
      color: black;
    }
    h4 {
      font-size: 30px;
      color: white;
    }
    .demo
    {
       font-family: sans-serif;
       margin: auto;
       text-align: center;
       width: 50%;
       border: 3px solid #000000;
       padding: 10px;
       background: #558ED5;
    }
    h1 {
      font-size: 36px;
      color: black;
    }
    h4 {
      font-size: 30px;
      color: white;
    }
  </style>
  <body>
    <div class="demo">
      <h1>AJAX Multiple Values</h1><br>
      <button type="button" onclick="sendData(1)">LED ON</button>
      <button type="button" onclick="sendData(0)">LED OFF</button><BR>
      </div>

     <div class = "displayobject">
      <br>LED State is : <span id="LEDState">NA</span>
       <h4>Value 1 : <span id="value1">0</span>&deg</h4>
       <h4>Value 2 : <span id="value2">0</span>%</h4>
       <h4>Value 3: <span id="value3">0</span>hPa</h4><br>
     </div>
     <script>
       setInterval(function() {getSensorData();}, 1000); // Call the update function every set interval e.g. 1000mS or 1-sec
  

       function sendData(led) 
{
  /*
      new XMLHttpRequest();
        - Reference link : https://www.w3schools.com/js/js_ajax_http.asp
        - Used to exchange data with webserver behind the scenes
  */

  // Create XMLHttpRequest Object
  var xhttp = new XMLHttpRequest();
  /*
      Define a Callback Function xhttp.onreadystatechange = function() 
        - xhttp.onreadystatechange = function() 
        - What's a callback function 
          - A function that's passed as a parameter to another function
          - Should have the code to execute when the response is ready
  */

  // Another callback function
  xhttp.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      /*
        this.readyState
          - Reference : https://developer.mozilla.org/en-US/docs/Web/API/XMLHttpRequest/readyState
          - Returns the state an XMLHttpRequest client
          - Value |	  State	           |  Description
            -------------------------------------------------------------------------------------------
            0	    |   UNSENT	         |  Client has been created. open() not called yet.
            1	    |   OPENED	         |  open() has been called.
            2	    |   HEADERS_RECEIVED |  send() has been called, and headers and status are available.
            3	    |   LOADING	         |  Downloading; responseText holds partial data.
            4	    |   DONE	           |  The operation is complete.

        this.status
            - 200: "OK"
            - 403: "Forbidden"
            - 404: "Page not found"
          
            getElementById()
            - Used every time you want to manipulate/get info 
              from an element in your document

            this.responseText
              -Returns the server response as a JavaScript string
              - Contains content from the requested URL using the XMLHttpRequest
              - 
      */
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  /*
      xhttp.open()  
        - Reference link : https://www.w3schools.com/xml/ajax_xmlhttprequest_send.asp
        - What does it do
          - Sends request to server
        - Parameters
          - open(method,url,async)
            - Specifies the type of request
            - Method : The type of request -> GET or POST
            - URL    : The server (file) location
            - Async : true (Asynchronous) | false (synchronous)
          - The '+led'
            - Is considered a 'Unique ID'
            - Used to avoid getting a cahced result
              - cahced result : Area of memory that stores the result of a 
                DB query/query block for resue
  */
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  /*
    xhttp.send();
      - send()
        - Sends request to server 
        - Used for GET requests
      - send(string)
        - Sends request to server
        - Used for POST requests
  */
  xhttp.send();
}

       function getSensorData() {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("value1").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "value1", true);
        xhttp.send();
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("value2").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "value2", true);
        xhttp.send();
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("value3").innerHTML = this.responseText;}
        };  
        xhttp.open("GET", "value3", true);
        xhttp.send(); 
      }
    </script>
  </body>
</html>
)=====";