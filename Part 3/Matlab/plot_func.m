function z = plot_func(timeseries, color)
    display(timeseries);
    plot(timeseries.time,timeseries.signals.values, color)
end