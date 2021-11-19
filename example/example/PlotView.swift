//
//  PlotView.swift
//  example
//
//  Created by Szymon Gęsicki on 19/11/2021.
//

import Foundation
import Plot


class PlotView: UIPlotView, PlotViewDataSource {
    
    var data: [Float] = []
    
    func renderingPoints() -> [Point] {

        var output: [Point] = []
        
        /// Set X,Y
        for i in 0 ..< data.count {
            
            let x = (Double(i) / Double( data.count )) * Double(frame.width)
            output.append( Plot.Point(x: x, y: Double(data[i]) ) )
        }

        return output
    }
}
