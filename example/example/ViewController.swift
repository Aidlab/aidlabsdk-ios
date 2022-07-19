//
//  ViewController.swift
//  example
//
//  Created by Szymon Gęsicki on 19/11/2021.
//

import AidlabSDK
import CoreBluetooth
import UIKit

class ViewController: UIViewController, UITableViewDelegate, UITableViewDataSource, AidlabSDKDelegate, AidlabDelegate {
    
    struct Value {
        var description: String
        var value: String
    }

    private var aidlabSDK: AidlabSDK?
    private var values: [String: Value] = [:]
    private var timer: Timer!
    
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var ecgPlotter: PlotView!
    
    func didDiscover(_ aidlab: CBPeripheral, rssi: NSNumber) {
        
        let signals: [Signal] = [.battery, .temperature, .ecg]

        aidlabSDK?.stopScan()
        aidlabSDK?.connect(signals: signals, peripheral: aidlab, aidlabDelegate: self)

    }
    
    func didReceiveECG(_ aidlab: IAidlab, timestamp: UInt64, values: [Float]) {
        for value in values {
            ecgPlotter.data.append(value)
            if ecgPlotter.data.count > 2000 { ecgPlotter.data.remove(at: 0) }
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        values["connection"] = Value(description: "Aidlab is connected", value: "false")
        values["skin_temperature"] = Value(description: "Skin temperature", value: "-- C")
        values["battery_soc"] = Value(description: "Battery state of charge", value: "--")

        aidlabSDK = AidlabSDK(delegate: self)
        aidlabSDK?.scan()

        tableView.delegate = self
        tableView.dataSource = self

        ecgPlotter.dataSource = ecgPlotter

        timer = Timer.scheduledTimer(timeInterval: 1.0 / 30.0, target: self, selector: #selector(ViewController.update), userInfo: nil, repeats: true)
    }
    
    @objc func update() {

        if (UIApplication.shared.applicationState != .background) {
            ecgPlotter.render()
        }
    }

    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
       
        return values.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell: UITableViewCell? = tableView.dequeueReusableCell(withIdentifier: "LabelCell")

        if cell == nil {
            cell = UITableViewCell(style: UITableViewCell.CellStyle.subtitle, reuseIdentifier: "LabelCell")
        }

        cell!.textLabel?.text = Array(values.values)[indexPath.row].value
        cell!.detailTextLabel?.text = Array(values.values)[indexPath.row].description

        return cell!
    }

    func didDisconnect(_ aidlab: IAidlab, reason: DisconnectReason) {
        values["connection"] = Value(description: "Aidlab is connected", value: "false")
        tableView.reloadData()
        aidlabSDK?.scan()
    }
    
    func didConnect(_ aidlab: IAidlab) {
        values["connection"] = Value(description: "Aidlab is connected", value: "true")
        tableView.reloadData()
    }
    
    func didReceiveBatteryLevel(_ aidlab: IAidlab, stateOfCharge: UInt8) {
        values["battery_soc"] = Value(description: "Battery state of charge", value: "\(stateOfCharge)%")
        tableView.reloadData()
    }
    
    
    func didReceiveSkinTemperature(_ aidlab: IAidlab, timestamp: UInt64, value: Float) {
        values["skin_temperature"] = Value(description: "Skin temperature", value: "\(value) C")
        tableView.reloadData()
    }
    
    func didReceiveRespiration(_ aidlab: IAidlab, timestamp: UInt64, values: [Float]) { }
    
    func didReceiveSteps(_ aidlab: IAidlab, timestamp: UInt64, value: UInt64) { }

    func didReceiveAccelerometer(_ aidlab: IAidlab, timestamp: UInt64, ax: Float, ay: Float, az: Float) { }
    
    func didReceiveGyroscope(_ aidlab: IAidlab, timestamp: UInt64, qx: Float, qy: Float, qz: Float) { }
    
    func didReceiveMagnetometer(_ aidlab: IAidlab, timestamp: UInt64, mx: Float, my: Float, mz: Float) { }
    
    func didReceiveQuaternion(_ aidlab: IAidlab, timestamp: UInt64, qw: Float, qx: Float, qy: Float, qz: Float) { }
    
    func didReceiveOrientation(_ aidlab: IAidlab, timestamp: UInt64, roll: Float, pitch: Float, yaw: Float) { }
    
    func didReceiveBodyPosition(_ aidlab: IAidlab, timestamp: UInt64, bodyPosition: BodyPosition) { }
    
    func didReceiveHeartRate(_ aidlab: IAidlab, timestamp: UInt64, heartRate: Int32) { }
    
    func didReceiveHrv(_ aidlab: IAidlab, timestamp: UInt64, hrv: Int32) { }
    
    func didReceiveRespirationRate(_ aidlab: IAidlab, timestamp: UInt64, value: UInt32) { }
    
    func didReceiveSoundVolume(_ aidlab: IAidlab, timestamp: UInt64, soundVolume: UInt16) { }
    
    func didDetect(_ aidlab: IAidlab, exercise: Exercise) { }
    
    func didDetect(_ aidlab: IAidlab, timestamp: UInt64, activity: ActivityType) { }
        
    func didReceiveError(_ aidlab: IAidlab, error: Error) { }
    
    func didReceiveRSSI(_ aidlab: IAidlab, rssi: Int32) { }
    
    func wearStateDidChange(_ aidlab: IAidlab, state: WearState) { }
    
    func didReceiveCommand(_ aidlab: IAidlab) { }
    
    func didReceiveMessage(_ aidlab: IAidlab, process: String, message: String) { }
    
    func didDetectUserEvent(_ aidlab: IAidlab, timestamp: UInt64) { }
    
    func didReceiveSignalQuality(_ timestamp: UInt64, value: Int32) { }
    
}

