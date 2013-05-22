package com;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class VideoViewer extends JFrame implements ChangeListener
{
    private DisplayPanel displayPanel;
    private JSlider bikeWheelSlider;
    private JLabel txtBikeWheelRate;
    private AbstractVideoPlayer videoPlayer;
    
    public VideoViewer() {
        
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        
        new DynamicParameters();
        
        displayPanel = new DisplayPanel();
        add(displayPanel, BorderLayout.NORTH);
        
        JPanel pn = new JPanel();
        bikeWheelSlider = new JSlider(JSlider.HORIZONTAL, 0, 5*Constants.sliderPadding, (int)DynamicParameters.getBikeWheelRateHz()*Constants.sliderPadding);
        bikeWheelSlider.addChangeListener(this);
        pn.add(bikeWheelSlider);
        txtBikeWheelRate = new JLabel("Wheel rate: " + (float)bikeWheelSlider.getValue() / (float)Constants.sliderPadding + " Hz");
        pn.add(txtBikeWheelRate);
        
        add(pn, BorderLayout.SOUTH);
       
        pack();
        setVisible(true);

        if(Constants.basicVideoPlayback)
            videoPlayer = new BasicVideoPlayer(displayPanel);
        else
            videoPlayer = new BikeWheelVideoPlayer(displayPanel);
        videoPlayer.startPlayback("vids\\out.raw");

    }

    @Override
    public void stateChanged(ChangeEvent arg0)
    {
        if(bikeWheelSlider.getValue() == 0)
            bikeWheelSlider.setValue(1);
        DynamicParameters.setBikeWheelRate((float)bikeWheelSlider.getValue() / (float)Constants.sliderPadding);
        txtBikeWheelRate.setText("Wheel rate: " + (float)bikeWheelSlider.getValue() / (float)Constants.sliderPadding + " Hz");
    }


}
