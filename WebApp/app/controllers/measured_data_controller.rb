require 'nokogiri'
require 'open-uri'

class MeasuredDataController < ApplicationController

	#POST \input 
	def create 
		doc = Nokogori::XML(open()) 
	end 
	
end
