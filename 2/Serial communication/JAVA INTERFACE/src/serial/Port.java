/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package serial;

import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

public class Port {

private CommPortIdentifier portId;
private SerialPort port;
private OutputStreamWriter out;
private InputStreamReader in;

public void open(String comportUsed) throws Exception {


  Enumeration portList;

  String defaultPort="";

  String osname = System.getProperty("os.name", "").toLowerCase();
  if (osname.startsWith("windows")) {
  // windows
    defaultPort = "COM1";
  } else if (osname.startsWith("linux")) {
  // linux
    System.setProperty("gnu.io.rxtx.SerialPorts","/dev/tnt0:/dev/tnt1:/dev/tnt2:/dev/tnt3:/dev/tnt4:/dev/tnt5");   
    defaultPort = "/dev/ttyS0";
  } else if (osname.startsWith("mac")) {
  // mac
    defaultPort = "????";
  } else {
    System.out
    .println("Sorry, your operating system is not supported");
  }

  if(comportUsed.isEmpty())comportUsed=defaultPort;
        
  portList = CommPortIdentifier.getPortIdentifiers();
  while (portList.hasMoreElements()) {
    portId = (CommPortIdentifier) portList.nextElement();
    if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
      if (portId.getName().equals(comportUsed)) {
        System.out.println("Found port: " + comportUsed);
        break;
     }
    }
  }

  this.port = (SerialPort) this.portId.open(comportUsed, 2000);
  port.setSerialPortParams(9600, SerialPort.DATABITS_8,
  SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
  in = new InputStreamReader(port.getInputStream());
  out = new OutputStreamWriter(port.getOutputStream());
  System.err.println("Port Open:Success");

}

public void write(String s) throws Exception {

  out.write(s);
  out.flush();
}

public void write(byte s) throws Exception {
  out.write(s);
  out.flush();
}

public void write(int s) throws Exception {
  out.write(s);
  out.flush();
}


public String reads() throws Exception {
  int n, i;
  char c;
  String answer = new String("");

  for (i = 0; i < 1000; i++)
  {
    while (in.ready()) {
      n = in.read();
      if (n != -1) {
        c = (char) n;
        answer = answer + c;
        Thread.sleep(1);
      } 
      else
        break;
    }
    delay(1);
  }
return answer;
}

public char read() throws Exception {
  int n, i;
  char c=0;
  
  while (! in.ready()) {
       delay(1);
  }
  
  n = in.read();
  if (n != -1) {
    c = (char) n;
  }
   
  return c;
}



private void delay(int a) {
  try {
    Thread.sleep(a);
  } catch (InterruptedException e) {
  }
}



public void close() throws Exception {
  try {
    port.close();
    System.err.println("close port");
  } catch (Exception e) {
    System.err.println("Error: close port failed: " + e);
  }
}


}