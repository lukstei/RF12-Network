module MeasuredDataHelper
	
	def data_chart_series(sensor, start_time)
		(start_time.to_date..Date.today).map {|date| MeasuredData.total_mean_on(sensor, date).to_f}		
	end
end
