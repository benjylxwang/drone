# drone

An Arduino project for a fully functioning drone

## Communication Protocol 

Communication between controller and drone is over the nRF24L01 modules. These allow for the sending and receiving of a 32 byte payload.

### Controller to Drone
The following is a list of all the controls needed and their position in the payload:

<table>
    <thead>
        <tr>
            <th>Byte #</th>
            <th>Control</th>
            <th>Type</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>0</td>
            <td rowspan=2>Throttle (Forwards/Backwards)</td>
            <td rowspan=2>int16</td>
        </tr>
        <tr>
            <td>1</td>
        </tr>
        <tr>
            <td>2</td>
            <td rowspan=2>Throttle (Left/Right)</td>
            <td rowspan=2>int16</td>
        </tr>
        <tr>
            <td>3</td>
        </tr>
        <tr>
            <td>4</td>
            <td rowspan=2>Throttle (Up/Down)</td>
            <td rowspan=2>int16</td>
        </tr>
        <tr>
            <td>5</td>
        </tr>
        <tr>
            <td>6-31</td>
            <td><i>Not in use</i></td>
            <td></td>
        </tr>
    </tbody>
</table>

### Drone to Controller
The following is a list of all the sensor and state data that will be sent back and their position in the payload:


<table>
    <thead>
        <tr>
            <th>Byte #</th>
            <th>Control</th>
            <th>Type</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>0</td>
            <td rowspan=4>Speed</td>
            <td rowspan=4>float</td>
        </tr>
        <tr>
            <td>1</td>
        </tr>
        <tr>
            <td>2</td>
        </tr>
        <tr>
            <td>3</td>
        </tr>
        <tr>
            <td>4</td>
            <td rowspan=4>Altitude</td>
            <td rowspan=4>float</td>
        </tr>
        <tr>
            <td>5</td>
        </tr>
        <tr>
            <td>6</td>
        </tr>
        <tr>
            <td>7</td>
        </tr>
        <tr>
            <td>8-31</td>
            <td><i>Not in use</i></td>
            <td></td>
        </tr>
    </tbody>
</table>